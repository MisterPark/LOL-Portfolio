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
sampler ShadowMapOptionSampler = sampler_state
{
	texture = g_shadowOptionMap;
	minfilter = linear;
	magfilter = linear;
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
	//float z = tex2D(DepthMapSampler, input.vUV).g / g_farZ;

	//float fogFactor = 1.0f / pow(2.71828f, pow(z * 0.66f, 3));
	//finalColor = input.fogFactor * textureColor + (1.0 - input.fogFactor) * fogColor;
	//vColor = fogFactor * vColor + (1.f - fogFactor);
	vColor.a = vAlbedo.a;
	return vColor;
}
float4 ps_tone_combine(PS_IN input) :COLOR0
{
	float4 vAlbedo = tex2D(AlbedoMapSampler, input.vUV);
	if (vAlbedo.a < 0.1f)
	{
		discard;
	}
	float4 vShade = tex2D(ShadeMapSampler, input.vUV);
	float4 vSpecular = tex2D(SpecularMapSampler, input.vUV);
	float4 vColor = vSpecular + vAlbedo * vShade;
	//vColor.r += 0.5f;
	//float z = tex2D(DepthMapSampler, input.vUV).g / g_farZ;

	//float fogFactor = 1.0f / pow(2.71828f, pow(z * 0.66f, 3));
	//finalColor = input.fogFactor * textureColor + (1.0 - input.fogFactor) * fogColor;
	//vColor = fogFactor * vColor + (1.f - fogFactor);
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
	
	float depth = tex2D(DepthMapSampler, input.vUV).r;
	float z = tex2D(DepthMapSampler, input.vUV).g;
	float4 vPosition = mul(float4(input.vClipPosition.xy, depth, 1.f) * z, g_mInverseViewProj);
	float4 vLightSpacePosition = mul(vPosition, g_mLightSpace);
	//투영좌표를 UV좌표로 변환시킨다.
	float2 shadowMapUV;

	shadowMapUV.x = vLightSpacePosition.x * 0.5f + 0.5f;
	shadowMapUV.y = -vLightSpacePosition.y * 0.5f + 0.5f;

	float2 shadowDepthColor = tex2D(ShadowMapSampler, saturate(shadowMapUV) );
	int shadowOption = tex2D(ShadowMapOptionSampler, saturate(shadowMapUV));
	//shadowMapUV = abs(shadowMapUV);
	
	float shadowDepth = shadowDepthColor.r/(shadowDepthColor.g * 2000.f) ;
	float4 vDiffuse = g_vLightAmbient;
	
	float currentDepth = (vLightSpacePosition.z / vLightSpacePosition.w);
	if (shadowMapUV.x < 0.f || shadowMapUV.x > 1.f || shadowMapUV.y < 0.f || shadowMapUV.y > 1.f)
	{

	}
	//현재 깊이가 그림자 맵의 뎁스보다 작아야, 조명을 계산한다
	else if (currentDepth < shadowDepth + 0.0000125f)
	{
		float3 vNormal = normalize(vNormalFactor.xyz * 2.f - 1.f);
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
	output.vShadow = float4(shadowOption.xx, 0.f, 0.f);
	output.vColor = vDiffuse;
	return output;
}
PS_OUT ps_directional_light_noshadow(PS_IN input)
{
	PS_OUT output;
	output.vSpecular = float4(0.f, 0.f, 0.f, 1.f);
	output.vShadow = float4(1.f, 1.f, 1.f, 1.f);
	float4 vSpecular = tex2D(SpecularMapSampler, input.vUV);
	float4 fPower = vSpecular.w;
	vSpecular.w = 1.f;

	float4 vNormalFactor = tex2D(NormalMapSampler, input.vUV);

	float depth = tex2D(DepthMapSampler, input.vUV).r;
	float z = tex2D(DepthMapSampler, input.vUV).g;
	float3 vNormal = normalize(vNormalFactor.xyz * 2.f - 1.f);

	float4 vPosition = mul(float4(input.vClipPosition.xy, depth, 1.f) * z, g_mInverseViewProj);
	float4 vLightDir = normalize(float4(g_vLightDirectionAndPower.xyz, 0.f));
	float intensity = saturate(dot(vLightDir * -1, vNormal));
	float4 vDiffuse = intensity * g_vLightDiffuse + g_vLightAmbient;
	vDiffuse.a = intensity;
	if (intensity > 0.f)
	{
		output.vSpecular = CalcSpecular(vSpecular, vLightDir.xyz, vNormal.xyz, vPosition.xyz, fPower);
		output.vSpecular.a = 1.f;
	}
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
		VertexShader = compile vs_3_0 vs_main();
		PixelShader = compile ps_3_0 ps_directional_light();
	}
	pass directioanl_no_shadow
	{
		ZEnable = false;
		VertexShader = compile vs_3_0 vs_main();
		PixelShader = compile ps_3_0 ps_directional_light_noshadow();
	}
}