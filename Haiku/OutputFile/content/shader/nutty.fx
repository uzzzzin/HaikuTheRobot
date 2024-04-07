#ifndef _nutty
#define _nutty

#include "value.fx"
#include "func.fx"

struct VS_IN
{
    float4 vColor : COLOR;
    float3 vPos : POSITION; // Sementic
    float2 vUV : TEXCOORD;
};

struct VS_OUT
{
    float4 vPosition : SV_Position;
    float4 vColor : COLOR;
    float2 vUV : TEXCOORD;
    
    float3 vWorldPos : POSITION;
};

VS_OUT VS_nutty(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWVP);
    output.vColor = _in.vColor;
    output.vUV = _in.vUV;
    
    if (0 == g_int_0)
    {
        output.vUV.x = _in.vUV.x;
    }
    else
    {
        output.vUV.x = 1 - _in.vUV.x;
    }
    
    output.vWorldPos = mul(float4(_in.vPos, 1.f), g_matWorld);

    return output;
}

#endif