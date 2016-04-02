//***************************************************************************************
// color.fx by Frank Luna (C) 2011 All Rights Reserved.
//
// Transforms and colors geometry.
//***************************************************************************************

cbuffer cbPerObject
{
	float4x4 gWorldViewProj;
    float gTime;
};

struct VertexIn
{
	float3 PosL  : POSITION;
    float4 Color : COLOR;
    float2 UVCoordinates : UVCOORDINATES;
};

struct VertexOut
{
	float4 PosH  : SV_POSITION;
    float2 UVCoordinates : UVCOORDINATES;
};

VertexOut VS(VertexIn vin)
{
	VertexOut vout;
	
    vout.PosH = mul(float4(vin.PosL, 1.0f), gWorldViewProj);
    vout.UVCoordinates = vin.UVCoordinates;
    
    return vout;
}

float4 PS(VertexOut a_Input) : SV_Target
{
    float distanceFromCenter = length(a_Input.UVCoordinates - float2(0.5f, 0.5f));

    float grayScale = 0.5f * cos(distanceFromCenter * 0.5f - gTime * 0.1f) + 0.5f;
    grayScale = 0.5f * cos(distanceFromCenter * 0.5f * 800.0f - gTime * 25.0f) + 0.5f;
    return float4(grayScale, grayScale, grayScale, 1.0f);
}

technique11 ColorTech
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_5_0, VS() ) );
        SetPixelShader( CompileShader( ps_5_0, PS() ) );
    }
}
