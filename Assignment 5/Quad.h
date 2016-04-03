#pragma once
#include <d3dUtil.h>

class Quad
{
private:
    ID3DX11Effect* m_Shader = nullptr;
    ID3D11Buffer* m_VertexBuffer = nullptr;
    ID3D11Buffer* m_IndexBuffer = nullptr;
    ID3DX11EffectMatrixVariable* m_ShaderMVP = nullptr;
    ID3DX11EffectShaderResourceVariable* m_ShaderDiffuse = nullptr;
    ID3D11ShaderResourceView* m_DiffuseSRV = nullptr;
    XMFLOAT2 m_Dimensions;
    std::wstring m_TexturePath;
    XMFLOAT3 m_Position;

public:
    Quad(CXMVECTOR a_Dimensions, const std::wstring& a_TexturePath);
    ~Quad();

    void setPosition(CXMVECTOR a_Position);
    void setTexture(ID3D11ShaderResourceView* a_Texture);
    void initialise(ID3D11Device* a_Device);
    void initialiseBuffers(ID3D11Device* a_Device);
    void draw(ID3D11DeviceContext* a_Context, CXMMATRIX a_ViewProjection);
    void setShader(ID3DX11Effect* a_Shader);
private:
    void bind(ID3D11DeviceContext* a_Context);
};