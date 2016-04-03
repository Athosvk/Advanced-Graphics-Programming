#pragma once
#include <Windows.h>
#include <xnamath.h>
#include <d3dUtil.h>

struct Vertex
{
    XMFLOAT3 Position;
    XMFLOAT4 Color;
    XMFLOAT3 Normal;
    XMFLOAT2 UVCoordinates = XMFLOAT2(0.0f, 0.0f);

    Vertex() = default;

    Vertex(FXMVECTOR a_Position, FXMVECTOR a_Color = Colors::White, FXMVECTOR a_Normal = XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f),
        CXMVECTOR a_UVCoordinates = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f))
    {
        XMStoreFloat3(&Position, a_Position);
        XMStoreFloat4(&Color, a_Color);
        XMStoreFloat3(&Normal, a_Normal);
        XMStoreFloat2(&UVCoordinates, a_UVCoordinates);
    }

    Vertex(XMFLOAT3 a_Position, XMFLOAT4 a_Color = reinterpret_cast<const float*>(&Colors::White),
        XMFLOAT3 a_Normal = XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT2 a_UVCoordinates = XMFLOAT2(0.0f, 0.0f))
        : Position(a_Position), Color(a_Color), Normal(a_Normal),
        UVCoordinates(a_UVCoordinates)
    {
    }
};