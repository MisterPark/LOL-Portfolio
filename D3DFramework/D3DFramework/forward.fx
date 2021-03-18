struct VSIn
{
	float4 vPosition:POSITION;
	float4 vNormal:NORMAL;
	float2 vUV:TEXCOORD0;
};
struct VSOut
{
	float4 vPosition:POSITION;
	float4 vNormal:NORMAL0;
	float2 vUV:TEXCOORD1;
	float4 vClipPosition:TEXCOORD2;
};
struct PSIn
{
	float4 vNormal:NORMAL0;
	float2 vUV:TEXCOORD1;
	float4 vClipPosition:TEXCOORD2;
};
matrix g_mWorld;
matrix g_mViewProj;
texture g_diffuseTexture;
sampler DiffuseTextureSampler = sampler_state
{
	texture = g_diffuseTexture;
	minfilter = linear;
	magfilter = linear;
	addressU = wrap;
	addressV = wrap;
};

VSOut vs_main(VSIn input)
{
	VSOut output;
	float4 vPosition = float4(input.vPosition.xyz, 1.f);
	vPosition = mul(vPosition, g_mWorld);
	vPosition = mul(vPosition, g_mViewProj);
	output.vPosition = vPosition;
	output.vClipPosition = vPosition;
	output.vNormal = mul(float4(input.vNormal.xyz, 0.f), g_mWorld);
	output.vUV = input.vUV;
	return output;
}
float4 ps_missile(PSIn input) :COLOR0
{
	return tex2D(DiffuseTextureSampler, input.vUV);
}
technique Default_Device
{
	pass Missile
	{
		AlphaBlendEnable = true;
		SrcBlend = srcalpha;
		DestBlend = invsrcalpha;
		VertexShader = compile vs_3_0 vs_main();
		PixelShader = compile ps_3_0 ps_missile();
		cullmode = none;
	}
}