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
texture g_timerMap;
texture g_gradientMap;
float4 g_uvRatioStart;
float4 g_uvRatioEnd;
float g_timerThresHold;
float4 g_timerColor;
matrix g_mWorld;
matrix g_mViewProj;
matrix g_mSightSpace;
bool g_grayscale;
float g_gradientmapMaxCnt;
float g_gradientmapIndex;
float4 g_multipleColor;
float g_alpha;

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
sampler TimerMapTextureSampler = sampler_state
{
	texture = g_timerMap;
	minfilter = linear;
	magfilter = linear;

	addressU = clamp;
	addressV = clamp;
};
sampler GradientMapSampler = sampler_state
{
	texture = g_gradientMap;
	minfilter = point;
	magfilter = point;

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
	if (vTex.x < g_uvRatioStart.x || vTex.x > g_uvRatioEnd.x || vTex.y < g_uvRatioStart.y || vTex.y > g_uvRatioEnd.y)
	{
		return float4(0.f, 0.f, 0.f, 0.f);
	}
	float2 timerTex = vTex / g_uvRatioEnd.xy;
	float timer = step(1.f - g_timerThresHold, tex2D(TimerMapTextureSampler, timerTex).r);
	float4 vAlbedo = tex2D(TextureSampler, input.vTex);

	if(g_gradientmapMaxCnt > 0) {
		float a = vAlbedo.r;
		vAlbedo.rgb = tex2D(GradientMapSampler, float2(vAlbedo.r, g_gradientmapIndex / g_gradientmapMaxCnt));
		if(a > 0.5f) {
			vAlbedo.a *= 5;
			//vAlbedo.a = a;
		} else {
			vAlbedo.a = a;
		}
	}

	if(g_grayscale) {
		vAlbedo.rgb = (vAlbedo.r + vAlbedo.g + vAlbedo.b) / 3;
	}
	//vAlbedo.rgb *= timer * 0.5f + 0.5f;
	//vAlbedo.rgb = (vAlbedo.rgb * (1.f - g_timerColor.a)) + (g_timerColor.rgb * g_timerColor.a * timer);
	//vAlbedo.rgb = (vAlbedo.rgb * (1.f - g_timerColor.a)) + (g_timerColor.rgb * g_timerColor.a * timer);
	vAlbedo.rgb = (vAlbedo.rgb * (1.f - g_timerColor.a * (!timer))) + (g_timerColor.rgb * g_timerColor.a * (!timer));

	vAlbedo.a *= g_alpha;

	return vAlbedo;
}
float4 ps_sight_main(PS_IN input) :COLOR0
{
	float2 vTex = input.vTex;
	if (vTex.x < g_uvRatioStart.x || vTex.x > g_uvRatioEnd.x || vTex.y < g_uvRatioStart.y || vTex.y > g_uvRatioEnd.y)
	{
		return float4(0.f, 0.f, 0.f, 0.f);
	}
	float4 vAlbedo = tex2D(TextureSampler, input.vTex);
	if(g_grayscale) {
		vAlbedo.rgb = (vAlbedo.r + vAlbedo.g + vAlbedo.b) / 3;
	}
	float2 sightTex = input.vTex;
	
	sightTex -= 0.5f;
	sightTex *= 2.f;
	//
	sightTex *= 0.5f;
	sightTex += 0.5f;
	float sight = tex2D(SightMapTextureSampler, sightTex).r;
	vAlbedo.rgb = vAlbedo.rgb* (sight * 0.5f + 0.5f);

	vAlbedo.a *= g_alpha;

	return vAlbedo;
}


float4 ps_timer_main(PS_IN input) :COLOR0
{
	float2 vTex = input.vTex;
	if (vTex.x < g_uvRatioStart.x || vTex.x > g_uvRatioEnd.x || vTex.y < g_uvRatioStart.y || vTex.y > g_uvRatioEnd.y)
	{
		return float4(0.f, 0.f, 0.f, 0.f);
	}
	float2 timerTex = vTex / g_uvRatioEnd.xy;
	float timer = step(1.f - g_timerThresHold, tex2D(TimerMapTextureSampler, timerTex).r);
	float4 vAlbedo = tex2D(TextureSampler, input.vTex);
	if(g_grayscale) {
		vAlbedo.rgb = (vAlbedo.r + vAlbedo.g + vAlbedo.b) / 3;
	}
	vAlbedo.rgb *= timer * 0.5f + 0.5f;

	vAlbedo.a *= g_alpha;

	return vAlbedo;
}

float4 ps_multiple_main(PS_IN input) :COLOR0
{
	float2 vTex = input.vTex;
	float4 vAlbedo = tex2D(TextureSampler, input.vTex);
	vAlbedo.rgb = (g_multipleColor.rgb * vAlbedo.rgb) / 1;
	
	vAlbedo.a *= g_alpha;

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
		PixelShader = compile ps_3_0 ps_sight_main();
	}

	pass Timer
	{
		ZEnable = false;
		AlphaBlendEnable = true;
		SrcBlend = srcalpha;
		DestBlend = invsrcalpha;
		VertexShader = compile vs_3_0 vs_main();
		PixelShader = compile ps_3_0 ps_timer_main();
	}

	pass Multiple
	{
		ZEnable = false;
		AlphaBlendEnable = true;
		SrcBlend = srcalpha;
		DestBlend = invsrcalpha;
		VertexShader = compile vs_3_0 vs_main();
		PixelShader = compile ps_3_0 ps_multiple_main();
	}
}