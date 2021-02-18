//for common
matrix g_mCameraProj;
matrix g_mWorld;
//matrix g_mNormalWorld;
texture g_diffuseTexture;
sampler DiffuseTextureSampler = sampler_state
{
	texture = g_diffuseTexture;
	minfilter = linear;
	magfilter = linear;
	addressU = wrap;
	addressV = wrap;
};
//for no specularmap
struct VSIn
{
	float4 vPosition:POSITION;
	float4 vNormal:NORMAL;
	float2 vUV:TEXCOORD0;
};
struct VSOut
{
	float4 vPosition:POSITION;
	float2 vUV:TEXCOORD1;
	float4 vClipPosition:TEXCOORD2;
};
struct PSIn
{
	float2 vUV:TEXCOORD1;
	float4 vClipPosition:TEXCOORD2;
};
struct PSOut
{
	float4 depth:COLOR0;
};
VSOut VS_main(VSIn input)
{
	VSOut output;
	float4 vPosition = float4(input.vPosition.xyz, 1.f);
	vPosition = mul(vPosition, g_mWorld);
	vPosition = mul(vPosition, g_mCameraProj);
	output.vPosition = vPosition;
	output.vClipPosition = vPosition;
	output.vUV = input.vUV;
	return output;
}
PSOut PS_main_NonAlpha(PSIn input)
{
	float depth = input.vClipPosition.z / input.vClipPosition.w;
	PSOut output;

	output.depth.rgba = 0.f;
	output.depth.r = depth;
	output.depth.g = input.vClipPosition.w;
	return output;
}
float g_alphaThreshold;
PSOut PS_main_AlphaTest(PSIn input)
{
	float4 diffuse = tex2D(DiffuseTextureSampler, input.vUV);
	if (diffuse.a < g_alphaThreshold)
	{
		discard;
	}
	float depth = input.vClipPosition.z / input.vClipPosition.w;
	output.depth.rgba = 0.f;
	output.depth.r = depth;
	output.depth.g = input.vClipPosition.w;
	return output;
}

technique Default_Device
{
	pass NonAlpha
	{
		SrcBlend = one;
		DestBlend = zero;
		vertexshader = compile vs_3_0 VS_main();
		pixelshader = compile ps_3_0 PS_main_NonAlpha();
	}
	pass AlphaTest
	{
		AlphaBlendEnable = true;
		SrcBlend = one;
		DestBlend = zero;
		vertexshader = compile vs_3_0 VS_main();
		pixelshader = compile ps_3_0 PS_main_AlphaTest();
	}
};