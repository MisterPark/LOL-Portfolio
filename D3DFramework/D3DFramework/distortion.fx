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


texture g_texture;
texture g_noiseTexture;
texture g_normalDepthMap;
sampler2D Sampler = sampler_state
{
    Texture = g_texture;
    AddressU = Clamp;
    AddressV = Clamp;
    MinFilter = Point;
    MagFilter = Point;
    MipFilter = Point;
};
sampler2D NoiseSampler = sampler_state
{
    Texture = g_noiseTexture;
    AddressU = Wrap;
    AddressV = Wrap;
    MinFilter = Linear;
    MagFilter = Linear;
    MipFilter = Linear;
};
sampler2D NormalDepthSampler = sampler_state
{
    Texture = g_normalDepthMap;
    AddressU = Clamp;
    AddressV = Clamp;
    MinFilter = Linear;
    MagFilter = Linear;
    MipFilter = Linear;
};
matrix g_mWorld;
matrix g_mViewProj;
float g_opacity;
VS_OUT vs_main(VS_IN input)
{
    VS_OUT output;
    output.vPosition = input.vPosition;
    output.vPosition.w = 1.f;
    output.vClipPosition = output.vPosition;
    output.vUV = input.vUV;
    return output;
}
VS_OUT vs_mesh_main(VS_IN input)
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
float4 distortion(float2 baseTex, float2 noiseTex)
{
    //float u = tex2D(NoiseSampler, tex.xy).r;
    //float v = tex2D(NoiseSampler, tex.yx).r;
    //return tex2D(Sampler, tex + (float2(u, v) * 2.f - 1.f) * 0.05f);

    float u = tex2D(NoiseSampler, noiseTex.xy).r;
    float v = tex2D(NoiseSampler, noiseTex.xy).g;
    return tex2D(Sampler, baseTex + (float2(u, v) * 2.f - 1.f) * 0.08f);
}
float4 ps_distortion(PS_IN input) :COLOR
{
    float2 Tex = input.vUV;
    float4 Color = 0;
    Color = tex2D(Sampler, Tex) * (1.f- g_opacity);
    Color += distortion(Tex, Tex) * g_opacity;
    return Color;
}
float4 ps_distortion_mesh(PS_IN input) :COLOR
{
    float2 Tex;
    float4 vPosition = input.vClipPosition;
    Tex = vPosition.xy;
    Tex /= vPosition.w;
    Tex.y *= -1.f;
    Tex = Tex * 0.5f + 0.5f;
    float4 Color = 0;
    //float depth = tex2D(NormalDepthSampler, Tex).a;
    Color = tex2D(Sampler, Tex);
    //1.0은 임의로 집어넣은 bias다. 필요에 따라 수정 가능 
    float opacity = tex2D(NoiseSampler, input.vUV).a * g_opacity;
    //if (depth + 1.0f >= vPosition.w)
    //{
        Color = Color * (1.f - opacity) + distortion(Tex, input.vUV) * opacity;
    //}
    return Color;
    //return tex2D(NoiseSampler, input.vUV);
}
technique Default_Device
{
    pass distortion_wholeScreen
    {
        ZEnable = false;
        VertexShader = compile vs_3_0 vs_main();
        PixelShader = compile ps_3_0 ps_distortion();
    }
    pass distortion_mesh
    {
        ZEnable = false;
		AlphaBlendEnable = true;
        VertexShader = compile vs_3_0 vs_mesh_main();
        PixelShader = compile ps_3_0 ps_distortion_mesh();
    }
}