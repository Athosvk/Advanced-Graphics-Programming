//***************************************************************************************
// color.fx by Frank Luna (C) 2011 All Rights Reserved.
//
// Transforms and colors geometry.
//***************************************************************************************

cbuffer cbPerObject
{
    float4x4 gWorldViewProj;
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

float4 PS(VertexOut a_Input) : SV_Target
{
    return float4(a_Input.Color.xyz, 0.7f);
}

BlendState AlphaBlend
{
    AlphaToCoverageEnable = FALSE;
    BlendEnable[0] = TRUE;
    SrcBlend = SRC_ALPHA;
    DestBlend = INV_SRC_ALPHA;
};

DepthStencilState Occlude
{
    DepthEnable = true;
    DepthWriteMask = WRITE_MASK_ALL;
    DepthFunc = COMPARISON_LESS;
    StencilEnable = true;
    StencilReadMask = 0xff;
    StencilWriteMask = 0xff;
    FrontFaceStencilFail = OP_KEEP;
    FrontFaceStencilDepthFailOp = OP_KEEP;
    FrontFaceStencilPassOp = OP_KEEP;
    FrontFaceStencilFunc = COMPARISION_EQUAL;
};

technique11 ColorTech
{
    pass P0
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS()));
        SetBlendState(AlphaBlend, float4(1, 1, 1, 1), 0xffffffff);
    }
}
