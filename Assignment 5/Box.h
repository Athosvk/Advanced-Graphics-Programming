#pragma once
#include <d3dUtil.h>

class Box
{
private:
    ID3D11Buffer* m_VertexBuffer = nullptr;
    ID3DX11Effect* m_Shader = nullptr;
    ID3DX11EffectMatrixVariable* m_ShaderMVP = nullptr;

public:
    Box();
    ~Box();

    void setShader(ID3DX11Effect* a_Shader);
    void draw(ID3D11DeviceContext* a_Context, CXMMATRIX a_ViewProjection);
    void constructVertexBuffer(ID3D11Device* a_Device);
private:
    void bind(ID3D11DeviceContext* a_Context);
};

