#ifndef _CHANGEROOM
#define _CHANGEROOM

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


void VS_ChangeRoom(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;

    
    if (0 == g_int_0)
    {

    }
    else
    {

    }
    
}

#endif