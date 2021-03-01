//for common
struct VS_IN
{
	float4 vPosition:POSITION;
	float2 vUV: TEXCOORD0;
};
struct VS_OUT
{
	float4 vPosition:POSITION;
	float4 vClipPosition:TEXCOORD0;
	float2 vUV: TEXCOORD1;
};
struct PS_IN
{
	float4 vClipPosition:TEXCOORD0;
	float2 vUV: TEXCOORD1;
};
struct PS_OUT
{
	float4 vColor: COLOR0;
	float4 vSpecular:COLOR1;
	float4 vShadow:COLOR2;
};
texture g_normalMap;
texture g_specularMap;
texture g_depthMap;
texture g_shadeMap;
texture g_albedoMap;
texture g_shadowMap;
texture g_shadowOptionMap;
texture g_rimLightMap;
sampler ShadeMapSampler = sampler_state
{
	texture = g_shadeMap;
	minfilter = linear;
	magfilter = linear;
};
sampler SpecularMapSampler = sampler_state
{
	texture = g_specularMap;
	minfilter = linear;
	magfilter = linear;
};
sampler AlbedoMapSampler = sampler_state
{
	texture = g_albedoMap;
	minfilter = point;
	magfilter = point;
};
sampler DepthMapSampler = sampler_state
{
	texture = g_depthMap;
	minfilter = linear;
	magfilter = linear;
};
sampler NormalMapSampler = sampler_state
{
	texture = g_normalMap;
};
sampler ShadowMapSampler = sampler_state
{
	texture = g_shadowMap;
	minfilter = linear;
	magfilter = linear;
};
sampler RimLightMapSampler = sampler_state
{
	texture = g_rimLightMap;
};
VS_OUT vs_main(VS_IN input)
{
	VS_OUT output;
	output.vPosition = input.vPosition;
	output.vPosition.w = 1.f;
	output.vClipPosition = output.vPosition;
	output.vUV = input.vUV;
	return output;
}
matrix g_mView;
float2 TexelKernel[8];
float3 DecodeNormal(float2 enc)
{
	float2 fenc = enc * 4 - 2;
	float f = dot(fenc, fenc);
	float g = sqrt(1 - f / 4.f);
	float3 n;
	n.xy = fenc * g;
	n.z = 1 - f / 2.f;
	return n;
}
float3 GetNormal(float2 tex)
{
	return DecodeNormal(tex2D(NormalMapSampler, tex).rg);
}
float EdgeDetect(float2 tex)
{
	float3 orig = GetNormal(tex);
	float sum = 0;
	for (int i = 0; i < 8; i++)
		sum += saturate(1 - dot(orig, GetNormal( tex + TexelKernel[i])));
	return smoothstep(0.5f, 1.5f, sum);
}
float RimLight(float2 tex)
{
	//림라이트의 4번째 요소는 오브젝트의 ID를 박았다.
	//이것의 차로 엣지를 디텍트하자.
	float orig = tex2D(RimLightMapSampler, tex).a;
	float sum = 0;
	for (int i = 0; i < 8; i++)
		sum += abs(orig - tex2D(RimLightMapSampler, tex + TexelKernel[i]).a);
	return smoothstep(0.f, 0.0001220721751f/4.f, sum);
}
float4 ps_combine(PS_IN input) :COLOR0
{
	float4 vAlbedo = tex2D(AlbedoMapSampler, input.vUV);
	if (vAlbedo.a < 0.1f)
	{
		discard;
	}
	float4 vShade = tex2D(ShadeMapSampler, input.vUV);
	float4 vSpecular = tex2D(SpecularMapSampler, input.vUV);
	float4 vColor = vSpecular + vAlbedo * vShade;
	//아웃라인 구현을 위한 추가 코드
	float4 vNormalMapFactor = tex2D(NormalMapSampler, input.vUV);
	float3 vNormal = DecodeNormal(vNormalMapFactor.rg);
	//vNormal = mul(float4(vNormal, 0.f), g_mView).xyz;
	//vNormal *= -1.f;
	//
	float3 vRimLightColor = tex2D(RimLightMapSampler, input.vUV).rgb;
	float rimLightAlpha = RimLight(input.vUV);
	vColor.rgb = vColor.rgb * (1 - rimLightAlpha) + vRimLightColor * rimLightAlpha;
	vColor.a = vAlbedo.a;
	return vColor;
}
matrix g_mLightSpace;
matrix g_mInverseViewProj;
float4 g_vLightDirectionAndPower;
float4 g_vLightDiffuse;
float4 g_vLightAmbient;
float4 g_vCameraPosition;

float4 CalcSpecular(float4 vMatSpecular, float3 vLightDir, float3 vNormal, float3 vPosition, float fPower)
{
	float3 vReflect = reflect(vLightDir.xyz, vNormal.xyz).xyz;
	float3 vLook = normalize(vPosition.xyz - g_vCameraPosition.xyz);
	float power = pow(saturate(dot(vReflect, -vLook)), fPower);
	float4 vSpecular = (float4) power;
	return vSpecular * g_vLightDiffuse * vMatSpecular;
}
PS_OUT ps_directional_light(PS_IN input)
{
	PS_OUT output;
	float4 vAlbedo = tex2D(AlbedoMapSampler, input.vUV);

	output.vSpecular = float4(0.f, 0.f, 0.f, 1.f);
	float4 vSpecular = tex2D(SpecularMapSampler, input.vUV);
	float4 fPower = vSpecular.w;
	vSpecular.w = 1.f;

	float4 vNormalFactor = tex2D(NormalMapSampler, input.vUV);
	float3 vNormal;
	{
		float scale = 1.7777;
		float3 enc = float3(vNormalFactor.rg, 0.f);
		float3 nn =
			enc.xyz * float3(2 * scale, 2 * scale, 0) +
			float3(-scale, -scale, 1);
		float g = 2.0 / dot(nn.xyz, nn.xyz);
		float3 n;
		n.xy = g * nn.xy;
		n.z = g - 1;
		vNormal = n;
	}
	float depth = vNormalFactor.b;
	float z = vNormalFactor.a;
	float4 vPosition = mul(float4(input.vClipPosition.xy, depth, 1.f) * z, g_mInverseViewProj);
	float4 vLightSpacePosition = mul(vPosition, g_mLightSpace);
	//투영좌표를 UV좌표로 변환시킨다.
	float2 shadowMapUV;

	shadowMapUV.x = vLightSpacePosition.x * 0.5f + 0.5f;
	shadowMapUV.y = -vLightSpacePosition.y * 0.5f + 0.5f;

	float2 shadowDepthColor = tex2D(ShadowMapSampler, shadowMapUV);
	//shadowMapUV = abs(shadowMapUV);
	
	float shadowDepth = shadowDepthColor.r/(shadowDepthColor.g * 2000.f) ;
	float4 vDiffuse = (float4)1.f;
	
	float currentDepth = (vLightSpacePosition.z / vLightSpacePosition.w);
	//현재 깊이가 그림자 맵의 뎁스보다 작아야, 조명을 계산한다
	if (currentDepth - 0.0000125f < shadowDepth)
	{
		
		float4 vLightDir = normalize(float4(g_vLightDirectionAndPower.xyz, 0.f));
		float intensity = saturate(dot(vLightDir * -1, vNormal));
		vDiffuse = intensity * g_vLightDiffuse + g_vLightAmbient;
		vDiffuse.a = intensity;
		if (intensity > 0.f)
		{
			output.vSpecular = CalcSpecular(vSpecular, vLightDir.xyz, vNormal.xyz, vPosition.xyz, fPower);
			output.vSpecular.a = 1.f;
		}
	}
	else
	{
		vDiffuse = g_vLightAmbient;
	}
	output.vShadow = float4(0.f,0.f, 0.f, 0.f);
	output.vColor = vDiffuse;
	return output;
}
technique Default_Device
{
	pass combine
	{
		ZWriteEnable = false;
		AlphaBlendEnable = true;
		SrcBlend = srcalpha;
		DestBlend = invsrcalpha;
		VertexShader = compile vs_3_0 vs_main();
		PixelShader = compile ps_3_0 ps_combine();
	}
	pass directioanl
	{
		ZEnable = false;
		AlphaBlendEnable = true;
		SrcBlend = One;
		DestBlend = One;
		BlendOp = Add;
		VertexShader = compile vs_3_0 vs_main();
		PixelShader = compile ps_3_0 ps_directional_light();
	}
}