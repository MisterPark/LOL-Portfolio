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

VS_OUT vs_main(VS_IN input)
{
	VS_OUT output;
	output.vPosition = input.vPosition;
	output.vPosition.w = 1.f;
	output.vClipPosition = output.vPosition;
	output.vUV = input.vUV;
	return output;
}

static const int g_cKernelSize = 13;

float2 PixelKernel[g_cKernelSize] =
{
    { -6, 0 },
    { -5, 0 },
    { -4, 0 },
    { -3, 0 },
    { -2, 0 },
    { -1, 0 },
    {  0, 0 },
    {  1, 0 },
    {  2, 0 },
    {  3, 0 },
    {  4, 0 },
    {  5, 0 },
    {  6, 0 },
};

float2 TexelKernel[g_cKernelSize];


static const float BlurWeights[g_cKernelSize] =
{
    0.002216,
    0.008764,
    0.026995,
    0.064759,
    0.120985,
    0.176033,
    0.199471,
    0.176033,
    0.120985,
    0.064759,
    0.026995,
    0.008764,
    0.002216,
};
texture g_texture;

sampler2D Sampler = sampler_state
{
    Texture = g_texture;
    AddressU = Clamp;
    AddressV = Clamp;
    MinFilter = Point;
    MagFilter = Linear;
    MipFilter = Linear;
};

float4 ps_blur(PS_IN input) :COLOR
{
    float2 Tex = input.vUV;
    float4 Color = 0;
    for (int i = 0; i < g_cKernelSize; i++)
    {
        Color += tex2D(Sampler, Tex + TexelKernel[i].xy) * BlurWeights[i];
    }
    return Color;
}
technique Default_Device
{
	pass blur
	{
		ZEnable = false;
		VertexShader = compile vs_3_0 vs_main();
		PixelShader = compile ps_3_0 ps_blur();
	}
}