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

//Source: https://www.shadertoy.com/view/Xd3SDM

#define ZMAX 100.0
#define EP 0.01
#define ITER 50

void rotate(inout float2 p, float ang) 
{
    float c = cos(ang), s = sin(ang);
    p = float2(p.x*c - p.y*s, p.x*s + p.y*c);
}
//////////////////////////////////
//http://www.iquilezles.org/www/articles/distfunctions/distfunctions.htm
//////////////////////////////////
//subtract
float opS(float d1, float d2)
{
    return max(-d1, d2);
}

//intersection
float opI(float d1, float d2) 
{
    return max(d1, d2);
}

//union
float opU(float d1, float d2) 
{
    return min(d1, d2);
}

//weird sphere
float sph(float3 m, float r) 
{
    rotate(m.xy, gTime / 8.0f);
    rotate(m.yz, gTime / 8.0f);
    rotate(m.xz, gTime / 8.0f);

    float d = sin(gTime) / 10.0f + 0.9f;
    float bumps = sin(d * m.x) * sin(d * m.y) * sin(d * m.z);

    return length(m) - r + bumps;
}

float map(float3 m) 
{
    //top
    float top = sph(m, 10.0f);

    //subtract the top from the bottom to
    //get the bowl type of thing
    m.y -= 11.0f;
    float ng = opS(sph(m / 0.83f, 20.0f) * 0.83f, top);
    m.y += 12.0f;

    //put the ball in the middle
    return opU(ng, sph(m / 0.1f, 30.0f) * 0.1f);
}

//soft shadow function, pretty much a copy paste from
//https://www.shadertoy.com/view/Xds3zN
float softshadow(float3 ro, float3 rd)
{
    float res = 1.0;
    float t = 0.02;
    for(int i = 0; i < 8; ++i)
    {
        float h = map(ro + rd * t);
        res = min(res, 8. * h / t);
        t += clamp(h, 0.02, 0.1);
        if(h < 0.001 || t > 2.5)
        {
            break;
        }
    }
    return saturate(res);
}

float3 getNormal(float3 v) {

    float3 e = float3(EP, 0., 0.);
    return normalize(float3 (
        map(v + e.xyy) - map(v - e.xyy),
        map(v + e.yxy) - map(v - e.yxy),
        map(v + e.yyx) - map(v - e.yyx)
        ));
}

float march(float3 o, float3 r, out float3 m) {

    float t = 0.0f;

    for(int i = 0; i < ITER; i++)
    {
        m = o + r*t;
        float d = map(m);

        if(d < EP)
        {
            break;
        }
        else 
        {
            t += d;
            if(t >= ZMAX)
            { 
                break; 
            }
        }
    }
    return t;
}

float3 render(float3 cameraPos, float3 ray, float3 lightPos)
{
    float3 pos;
    float t = march(cameraPos, ray, pos);

    if(t < ZMAX)
    {
        float3 normal = getNormal(pos);

        float3 lightRay = normalize(pos - lightPos);
        float diffuse = max(0.0f, dot(normal, -lightRay));

        float3 reflectionDirection = reflect(lightRay, normal);
        float spectral = pow(max(dot(reflectionDirection, -ray), 0.0f), 10.0f);

        float3 diff = float3(1.0f, 0.0f, 0.0f) * diffuse;
        float3 spec = float3(1.0f, 1.0f, 1.0f) * spectral;
        float3 ambi = float3(0.4f, 0.0f, 0.0f);

        float sshadow = softshadow(pos, lightPos);

        diff *= sshadow;
        spec *= sshadow;

        //makes things close appear brighter
        float f = 1.0f / (1.0f + t * t * 0.002f);

        return (diff + spec + ambi) * f;
    }
    else 
    {
        //the background
        return float3(0.2f, 0.2f, 0.2f);
    }
}

float3 getRayDir(float2 screenPos, float3 origin, float3 lookAt, float3 up, float fov) {

    float3 d = normalize(lookAt - origin);
    float3 rayRight = normalize(cross(d, up));

    return normalize(screenPos.x*rayRight + screenPos.y*up +
        1.0 / tan(radians(fov / 2.0)) * d);
}

float4 PS(VertexOut a_Input) : SV_Target
{
    float3 cameraPos = float3(0.0f, 4.0f, 30.0f);
    float3 cameraUp = float3(0.0f, 1.0f, 0.0f);
    float3 cameraLookAt = float3(0.0f, -40.0f, -180.0f);

    float2 origin = a_Input.UVCoordinates * 2.0f - float2(1.0f, 1.0f);
    float3 lightPos = float3(sin(gTime) * 50.0f, 30.0f, cos(gTime) * 70.0f);
    float3 ray = getRayDir(origin, cameraPos, cameraLookAt, cameraUp, 25.0f);

    return float4(render(cameraPos, ray, lightPos), 1.0f);
}

technique11 ColorTech
{
    pass P0
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS()));
    }
}