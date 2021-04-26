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

matrix g_mWorld;
matrix g_mViewProj;
texture g_texture;
sampler2D Sampler = sampler_state
{
    Texture = g_texture;
    AddressU = Clamp;
    AddressV = Clamp;
    MinFilter = Point;
    MagFilter = Point;
    MipFilter = Point;
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

VS_OUT vs_mesh(VS_IN input)
{
    float4 vPosition = float4(input.vPosition.xyz, 1.f);
    vPosition = mul(vPosition, g_mWorld);
    vPosition = mul(vPosition, g_mViewProj);
    VS_OUT output;
    output.vPosition = vPosition;
    output.vClipPosition = vPosition;
    output.vUV = input.vUV;
    return output;
}

float4 ps_main(PS_IN input) :COLOR
{
    float2 Tex = input.vUV;
    float4 Color = tex2D(Sampler, Tex);

	Color.rgb = (Color.r + Color.g + Color.b) / 3;

    return Color;
}

float4 ps_mesh(PS_IN input) :COLOR
{
    float2 Tex;
    float4 vPosition = input.vClipPosition;
    Tex = vPosition.xy;
    Tex /= vPosition.w;
    Tex.y *= -1.f;
    Tex = Tex * 0.5f + 0.5f;
    float4 Color = 0;
    Color = tex2D(Sampler, Tex);
	Color.rgb = (Color.r + Color.g + Color.b) / 3;
    return Color;
}

technique Default_Device
{
    pass mono
    {
        ZEnable = false;
        VertexShader = compile vs_3_0 vs_main();
        PixelShader = compile ps_3_0 ps_main();
    }
    
    pass mono_mesh
    {
        ZEnable = false;
        VertexShader = compile vs_3_0 vs_mesh();
        PixelShader = compile ps_3_0 ps_mesh();
    }
}