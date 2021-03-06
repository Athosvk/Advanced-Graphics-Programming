//***************************************************************************************
// color.fx by Frank Luna (C) 2011 All Rights Reserved.
//
// Transforms and colors geometry.
//***************************************************************************************

cbuffer cbPerObject
{
	float4x4 gWorldViewProj;
};
texture2D gDiffuse;

struct VertexIn
{
	float3 PosL  : POSITION;
    float4 Color : COLOR;
    float2 UVCoordinates : UVCOORDINATES;
};

struct VertexOut
{
	float4 PosH  : SV_POSITION;
    float4 Color : COLOR;
    float2 UVCoordinates : UVCOORDINATES;
};

VertexOut VS(VertexIn vin)
{
	VertexOut vout;
	
    vout.PosH = mul(float4(vin.PosL, 1.0f), gWorldViewProj);
    vout.Color = vin.Color;
    vout.UVCoordinates = vin.UVCoordinates;
    
    return vout;
}

SamplerState AnisotropicSampler
{
    Filter = ANISOTROPIC;
    MaxAnisotropy = 4;

    AddressU = WRAP;
    AddressV = WRAP;
};

float4 PS(VertexOut a_Input) : SV_Target
{
    return gDiffuse.Sample(AnisotropicSampler, a_Input.UVCoordinates);
}

RasterizerState NoCull
{
    CullMode = None;
};

technique11 ColorTech
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_5_0, VS() ) );
        SetPixelShader( CompileShader( ps_5_0, PS() ) );
        SetRasterizerState(NoCull);
    }
}
