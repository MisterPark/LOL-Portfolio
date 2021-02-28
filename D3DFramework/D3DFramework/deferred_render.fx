//for common
matrix g_mViewProj;
matrix g_mView;
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
float4 g_vSpecular;
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
struct PSOut
{
	float4 diffuse:COLOR0;
	float4 normal:COLOR1;
	float4 specular:COLOR2;
};
VSOut VS_main(VSIn input)
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
PSOut PS_main_NonAlpha(PSIn input)
{
	float depth = input.vClipPosition.z / input.vClipPosition.w;
	PSOut output;

	output.diffuse = tex2D(DiffuseTextureSampler, input.vUV);
	output.diffuse.a = 1.f;
	output.specular = g_vSpecular;
	float3 vNormal = input.vNormal.xyz;
	float2 packingNormal = (float2)0;
	float2 depths = float2(depth, input.vClipPosition.w);
	float scale = 1.7777;
	packingNormal = vNormal.xy / (vNormal.z + 1);
	packingNormal /= packingNormal;
	packingNormal = packingNormal * 0.5 + 0.5;

	output.normal = float4(packingNormal, depths);

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
	PSOut output;
	output.diffuse = diffuse;
	output.diffuse.a = 1.f;

	float depth = input.vClipPosition.z / input.vClipPosition.w;

	output.specular = g_vSpecular;
	float3 vNormal = input.vNormal.xyz;
	float2 packingNormal = (float2)0;
	float2 depths = float2(depth, input.vClipPosition.w);
	float scale = 1.7777;
	packingNormal = vNormal.xy / (vNormal.z + 1);
	packingNormal /= packingNormal;
	packingNormal = packingNormal * 0.5 + 0.5;

	output.normal = float4(packingNormal, depths);

	return output;
}

technique Default_Device
{
	pass NonAlpha
	{
		AlphaBlendEnable = true;
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