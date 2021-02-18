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
};
texture g_normalMap;
texture g_specularMap;
texture g_depthMap;
texture g_shadeMap;
texture g_albedoMap;
texture g_shadowMap;
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
	return vAlbedo;
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
	return vAlbedo;
}
matrix g_mCvt2LightSpace;
matrix g_mInverseViewProj;
float4 g_vLightDirectionAndPower;
float4 g_vLightDiffuse;
float4 g_vLightAmbient;
float4 g_vCameraPosition;
PS_OUT ps_directional_light(PS_IN input)
{
	PS_OUT output;
	float4 vAlbedo = tex2D(AlbedoMapSampler, input.vUV);
	if (vAlbedo.a < 0.1f)
	{
		discard;
	}

	output.vSpecular = float4(0.f, 0.f, 0.f, 1.f);
	float4 vSpecular = tex2D(SpecularMapSampler, input.vUV);
	float4 fPower = vSpecular.w;
	vSpecular.w = 1.f;

	float4 vNormalFactor = tex2D(NormalMapSampler, input.vUV);
	
	float depth = tex2D(DepthMapSampler, input.vUV).r;
	float z = tex2D(DepthMapSampler, input.vUV).g;
	float4 vLightSpacePosition = mul(float4(input.vClipPosition.xy, depth, 1.f) * z, g_mCvt2LightSpace);
	//투영좌표를 UV좌표로 변환시킨다.
	vLightSpacePosition.xy *= 0.5f;
	vLightSpacePosition.xy += 0.5f;
	vLightSpacePosition.y *= -1.f;
	float2 shadowDepth = tex2D(ShadowMapSampler, vLightSpacePosition.xy);
	float4 vDiffuse = g_vLightAmbient;
	//z값만 비교하자
	if (shadowDepth.g > vLightSpacePosition.w)
	{
		float3 vNormal = normalize(vNormalFactor.xyz * 2.f - 1.f);
		float4 vPosition = mul(float4(input.vClipPosition.xy, depth, 1.f) * z, g_mInverseViewProj);
		float4 vLightDir = normalize(float4(g_vLightDirectionAndPower.xyz, 0.f));
		float intensity = saturate(dot(vLightDir * -1, vNormal));
		vDiffuse += intensity * g_vLightDiffuse;
		vDiffuse.a = intensity;
		if (intensity > 0.f)
		{
			float3 vReflect = reflect(vLightDir.xyz, vNormal.xyz).xyz;
			float3 vLook = normalize(vPosition.xyz - g_vCameraPosition.xyz);
			float power = pow(saturate(dot(vReflect, -vLook)), fPower);
			output.vSpecular = (float4) power;
			output.vSpecular = output.vSpecular * g_vLightDiffuse * vSpecular;
			output.vSpecular.a = 1.f;
		}
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
	pass tone_combine
	{
		ZWriteEnable = false;
		AlphaBlendEnable = true;
		SrcBlend = srcalpha;
		DestBlend = invsrcalpha;
		VertexShader = compile vs_3_0 vs_main();
		PixelShader = compile ps_3_0 ps_tone_combine();
	}
}