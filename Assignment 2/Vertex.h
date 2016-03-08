#pragma once
#include <Windows.h>
#include <xnamath.h>

struct Vertex
{
    XMFLOAT3 Position;
    XMFLOAT4 Color;
    XMFLOAT2 UVCoordinates = XMFLOAT2(0.0f, 0.0f);

    Vertex() = default;

    Vertex(FXMVECTOR a_Position, FXMVECTOR a_Color = Colors::White, 
        FXMVECTOR a_UVCoordinates = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f))
    {
        XMStoreFloat3(&Position, a_Position);
        XMStoreFloat4(&Color, a_Color);
        XMStoreFloat2(&UVCoordinates, a_UVCoordinates);
    }

    Vertex(XMFLOAT3 a_Position, XMFLOAT4 a_Color = reinterpret_cast<const float*>(&Colors::White),
        XMFLOAT2 a_UVCoordinates = XMFLOAT2(0.0f, 0.0f))
        : Position(a_Position), Color(a_Color),
        UVCoordinates(a_UVCoordinates)
    {
    }
};