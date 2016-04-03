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

float noise(float3 p) //Thx to Las^Mercury
{
    float3 i = floor(p);
    float4 a = dot(i, float3(1., 57., 21.)) + float4(0., 57., 21., 78.);
    float3 f = cos((p - i)*acos(-1.))*(-.5) + .5;
    a = lerp(sin(cos(a)*a), sin(cos(1. + a)*(1. + a)), f.x);
    a.xy = lerp(a.xz, a.yw, f.y);
    return lerp(a.x, a.y, f.z);
}

float sphere(float3 p, float4 spr)
{
    return length(spr.xyz - p) - spr.w;
}

float flame(float3 p)
{
    float d = sphere(p*float3(1.0f, 0.5f, 1.0f), float4(0.0f, -1.0f, 0.0f, 1.0f));
    return d + (noise(p + float3(0.0f, gTime*2.0f, 0.0f)) + noise(p*3.0f)*0.5f)*0.25f*(p.y);
}

float scene(float3 p)
{
    return min(100.0f - length(p), abs(flame(p)));
}

float4 raymarch(float3 org, float3 dir)
{
    float d = 0.0f, glow = 0.0f, eps = 0.02f;
    float3 p = org;
    bool glowed = false;

    for(int i = 0; i<64; i++)
    {
        d = scene(p) + eps;
        p += d * dir;
        if(d > eps)
        {
            if(flame(p) < 0.0f)
            {
                glowed = true;
            }
            if(glowed)
            {
                glow = float(i) / 64.0f;
            }
        }
    }
    return float4(p, glow);
}

float4 PS(VertexOut a_Input) : SV_Target
{
    float2 normalizedUV = a_Input.UVCoordinates * 2.0f - float2(1.0f, 1.0f);
    float3 origin = float3(0.0f, -2.0f, 4.0f);
    float3 direction = normalize(float3(normalizedUV.x * 1.6f,
        -normalizedUV.y, -1.5f));

    float4 position = raymarch(origin, direction);
    float glow = position.w;

    float4 col = lerp(float4(1.0f, 0.5f, 0.1f, 1.0f), float4(0.1f, 0.5f, 1.0f, 1.0f), 
        position.y * 0.02f + 0.4f);

    return lerp(float4(0.0f, 0.0f, 0.0f, 0.0f), col, pow(glow * 2.0f,4.0f));
}

technique11 ColorTech
{
    pass P0
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS()));
    }
}