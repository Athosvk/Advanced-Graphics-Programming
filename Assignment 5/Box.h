#pragma once
#include <d3dUtil.h>

class Box
{
private:
    ID3D11Buffer* m_VertexBuffer = nullptr;

public:
    Box();
    ~Box();

private:
    void constructVertexBuffer(ID3D11Device* a_Device);
};

