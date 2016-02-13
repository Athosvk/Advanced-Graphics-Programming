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
};

struct VertexOut
{
	float3 PosH  : POSITION;
    float4 Color : COLOR;
};

VertexOut VS(VertexIn vin)
{
	VertexOut vout;
	
    vout.PosH = vin.PosL;
    vout.Color = vin.Color;
    
    return vout;
}

struct Patch
{
    float EdgeFactors[3] : SV_TessFactor;
    float InsideFactor : SV_InsideTessFactor;
};

Patch ConstantHS(InputPatch<VertexOut, 3> a_InputPatch, uint a_PatchID : SV_PrimitiveID)
{
    Patch patch = (Patch)0;

    [unroll]
    for(int i = 0; i < 3; i++)
    {
        patch.EdgeFactors[i] = 2;
    }
    patch.InsideFactor = 2;
    return patch;
}

struct HullOutput
{
    float3 Position : POSITION;
    float4 Color : COLOR;
};

[domain("tri")]
[partitioning("fractional_odd")]
[outputtopology("triangle_cw")]
[outputcontrolpoints(3)]
[patchconstantfunc("ConstantHS")]
[maxtessfactor(64.0f)]
HullOutput HS(InputPatch<VertexOut, 3> a_InputPatch, uint a_ControlPointID : SV_OutputControlPointID, 
    uint a_PatchID : SV_PrimitiveID)
{
    HullOutput output = (HullOutput) 0;
    output.Position = a_InputPatch[a_ControlPointID].PosH;
    output.Color = a_InputPatch[a_ControlPointID].Color;
    return output;
}

struct DomainOutput
{
    float4 Position : SV_Position;
    float4 Color : COLOR;
};

[domain("tri")]
DomainOutput DS(Patch a_InputPatch, float3 a_UVW : SV_DomainLocation, const OutputPatch<HullOutput, 3> a_Triangle)
{
    DomainOutput output = (DomainOutput) 0;
    float3 vertexPosition = a_Triangle[0].Position * a_UVW.x + a_Triangle[1].Position * a_UVW.y +
        a_Triangle[2].Position * a_UVW.z;
    
    
    float3 rotatedVertexPosition = vertexPosition;
    float cosX = cos(vertexPosition.y * );
    float sinZ = sin(vertexPosition.y * 1.0f);

    rotatedVertexPosition.x = vertexPosition.x * cosX - vertexPosition.z * sinZ;
    rotatedVertexPosition.z = vertexPosition.z * cosX + vertexPosition.x * sinZ;

    output.Position = mul(float4(rotatedVertexPosition, 1.0f), gWorldViewProj);
    output.Color = a_Triangle[0].Color * a_UVW.x + a_Triangle[1].Color * a_UVW.y + a_Triangle[2].Color * a_UVW.z;
    return output;
}

float4 PS(DomainOutput a_Input) : SV_Target
{
    return a_Input.Color;
}

technique11 ColorTech
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_5_0, VS() ) );
        SetHullShader(CompileShader(hs_5_0, HS()));
        SetDomainShader(CompileShader(ds_5_0, DS()));
        SetPixelShader( CompileShader( ps_5_0, PS() ) );
    }
}
