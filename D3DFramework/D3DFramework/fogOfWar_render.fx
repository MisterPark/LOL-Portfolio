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
//시야의 범위(맵 기준 공간)
float g_sightRadius;
float g_sightRadius2;
//시야의 좌표(맵 기준 공간)
float4 g_vSightPosition;
//
matrix g_mWorld;
matrix g_mMapSpace;

texture g_heightMap;
sampler HeightMapSampler = sampler_state
{
	texture = g_heightMap;
	minfilter = point;
	magfilter = point;
};


VS_OUT vs_height_main(VS_IN input)
{
	VS_OUT output;
	float4 vPosition = input.vPosition;
	float  height;
	vPosition.w = 1.f;
	vPosition = mul(vPosition, g_mWorld);
	height = vPosition.y;
	vPosition = mul(vPosition, g_mMapSpace);
	output.vPosition = vPosition;
	output.vClipPosition = vPosition;
	output.vUV = float2(height, height);
	return output;
}
float4 ps_height(PS_IN input) :COLOR
{

	return float4(step(0.1f, (input.vUV.xxx - 60.f)/20.f), 1.f);
}


VS_OUT vs_main(VS_IN input)
{
	VS_OUT output;
	output.vPosition = input.vPosition;
	output.vPosition.w = 1.f;
	output.vClipPosition = output.vPosition;
	output.vUV = input.vUV;
	return output;
}
float4 ps_fogOfWar(PS_IN input) :COLOR
{
	//여기서 들어오는 UV및 Position은 렌더타겟의 그것이다.
	float4 vSightPosition = g_vSightPosition;
	float4 vPixelPosition = input.vClipPosition;
	
	vSightPosition.yz = vSightPosition.zy;
	vSightPosition.wz = float2(0.f, 0.f);
	vPixelPosition.wz = float2(0.f, 0.f);
	half len = g_sightRadius - length(vPixelPosition - vSightPosition);
	half bright = smoothstep(0.f, 1.f - g_sightRadius2 / g_sightRadius, len / g_sightRadius);
	if (bright <= 0.f)
	{
		discard;
	}
	float2 d = (vPixelPosition - vSightPosition).xy;
	float height;
	half2 xy = vSightPosition.xy;
	half2 tex = xy * 0.5f + 0.5f;

	tex.y *= -1.f;

	height = tex2D(HeightMapSampler, tex).r;
	half3 prevPosition = half3(xy.x, height, xy.y);
	float prevHeight = height;
	half sight = 1.f;
	for (int i = 0; i < 75; ++i)
	{
		xy += d * 1 / 75.f;
		tex = xy * 0.5f + 0.5f;
		tex.y *= -1.f;
		float nowHeight = tex2D(HeightMapSampler, tex).r;
		if (prevHeight <= nowHeight)
		{
			sight = 1.f;
			prevHeight = nowHeight;
		}
		else
		{

			discard;
		}
	}
	return sight * half4(bright.xxx, 1.f);
}
technique Default_Device
{
	pass height
	{
		VertexShader = compile vs_3_0 vs_height_main();
		PixelShader = compile ps_3_0 ps_height();
	}
	pass fogSight
	{
		ZEnable = false;
		AlphaBlendEnable = true;
		BlendOp = Max;
		SrcBlend = One;
		DestBlend = One;
		VertexShader = compile vs_3_0 vs_main();
		PixelShader = compile ps_3_0 ps_fogOfWar();
	}
}