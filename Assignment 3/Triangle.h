#pragma once
#include <d3dUtil.h>
#include <GeometryGenerator.h>

class Triangle
{
private:
    XMFLOAT4 m_Color;
    GeometryGenerator::MeshData m_MeshData;

public:
    Triangle(float a_Base, XMVECTOR a_Color = Colors::White);
};

