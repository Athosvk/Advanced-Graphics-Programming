#pragma once
#include <d3dUtil.h>

class Quad
{
private:
    ID3DX11Effect* m_Shader = nullptr;
    XMFLOAT4X4 m_Transform;
    ID3D11Buffer* m_IndexBuffer = nullptr;
    ID3D11Buffer* m_VertexBuffer = nullptr;
    ID3DX11EffectMatrixVariable* m_ShaderMVP;
    ID3DX11EffectScalarVariable* m_ShaderTime;
    float m_TimePassed = 0.0f;

public:
    Quad();
    ~Quad();

    void setShader(ID3DX11Effect* a_Shader);
    void setPosition(CXMVECTOR a_Position);
    void update(float a_DeltaTime);
    void draw(ID3D11DeviceContext* a_Context, CXMMATRIX a_ViewProjection);
    void initialiseBuffers(ID3D11Device* a_Device);
private:
    void bind(ID3D11DeviceContext* a_Context);
};

