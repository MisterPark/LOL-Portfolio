struct VS_IN
{
	float4 vPosition:POSITION;
	float2 vTex: TEXCOORD0;
};
struct VS_OUT
{
	float4 vPosition:POSITION;
	float4 vClipPosition:TEXCOORD0;
	float2 vTex: TEXCOORD1;
};
struct PS_IN
{
	float4 vClipPosition:TEXCOORD0;
	float2 vTex: TEXCOORD1;
};
texture g_texture;
texture g_sightMap;
float4 g_uvRatio;
matrix g_mWorld;
matrix g_mViewProj;
matrix g_mSightSpace;
sampler TextureSampler = sampler_state
{
	texture = g_texture;
	minfilter = linear;
	magfilter = linear;

	addressU = clamp;
	addressV = clamp;
};
sampler SightMapTextureSampler = sampler_state
{
	texture = g_sightMap;
	minfilter = linear;
	magfilter = linear;

	addressU = clamp;
	addressV = clamp;
};
VS_OUT vs_main(VS_IN input)
{
	VS_OUT output;
	float4 vPosition = float4(input.vPosition.xyz, 1.f);
	output.vPosition = mul(mul(vPosition, g_mWorld), g_mViewProj);
	output.vClipPosition = output.vPosition;
	output.vTex = input.vTex;
	return output;
}

float4 ps_main(PS_IN input) :COLOR0
{
	float2 vTex = input.vTex;
	if (vTex.x > g_uvRatio.x || vTex.y > g_uvRatio.y)
	{
		return float4(0.f, 0.f, 0.f, 0.f);
	}
	float4 vAlbedo = tex2D(TextureSampler, input.vTex);
	return vAlbedo;
}
float4 ps_sight_main(PS_IN input) :COLOR0
{
	float2 vTex = input.vTex;
	if (vTex.x > g_uvRatio.x || vTex.y > g_uvRatio.y)
	{
		return float4(0.f, 0.f, 0.f, 0.f);
	}
	float4 vAlbedo = tex2D(TextureSampler, input.vTex);
	float vSight = tex2D(SightMapTextureSampler, input.vTex).r;
	vAlbedo.rgb = vAlbedo.rgb* (vSight * 0.5f + 0.5f);
	return vAlbedo;
}
technique Default_Device
{
	pass HPBar
	{
		ZEnable = false;
		AlphaBlendEnable = true;
		SrcBlend = srcalpha;
		DestBlend = invsrcalpha;
		VertexShader = compile vs_3_0 vs_main();
		PixelShader = compile ps_3_0 ps_main();
	}

	pass SightMap
	{
		ZEnable = false;
		AlphaBlendEnable = true;
		SrcBlend = srcalpha;
		DestBlend = invsrcalpha;
		VertexShader = compile vs_3_0 vs_main();
		PixelShader = compile ps_3_0 ps_main();
	}
}