#pragma once
#include <Windows.h>
#include <xnamath.h>

struct Vertex
{
    XMFLOAT3 Pos;
    XMFLOAT4 Color;

    Vertex() = default;

    Vertex(FXMVECTOR aPosition, FXMVECTOR aColor = Colors::White)
    {
        XMStoreFloat3(&Pos, aPosition);
        XMStoreFloat4(&Color, aColor);
    }

    Vertex(XMFLOAT3 aPosition, XMFLOAT4 aColor = reinterpret_cast<const float*>(&Colors::White))
        : Pos(aPosition),
        Color(aColor)
    {
    }
};