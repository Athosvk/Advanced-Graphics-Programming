#pragma once
#include <d3dUtil.h>

class Box
{
private:
    ID3D11Buffer* m_VertexBuffer = nullptr;
    ID3DX11Effect* m_Shader = nullptr;

public:
    Box();
    ~Box();

    void setShader(ID3DX11Effect* a_Shader);
private:
    void constructVertexBuffer(ID3D11Device* a_Device);
    void bind(ID3D11DeviceContext* a_Context);
};

