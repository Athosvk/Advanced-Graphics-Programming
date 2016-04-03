#include <Vertex.h>
#include <array>

#include "Quad.h"

Quad::Quad(CXMVECTOR a_Dimensions, const std::wstring& a_TexturePath)
    : m_TexturePath(a_TexturePath)
{
    XMStoreFloat2(&m_Dimensions, a_Dimensions);
}

Quad::~Quad()
{
    ReleaseCOM(m_VertexBuffer);
    ReleaseCOM(m_IndexBuffer);
    ReleaseCOM(m_DiffuseSRV);
}

void Quad::setPosition(CXMVECTOR a_Position)
{
    XMStoreFloat3(&m_Position, a_Position);
}

void Quad::initialise(ID3D11Device* a_Device)
{
    HR(D3DX11CreateShaderResourceViewFromFile(a_Device, m_TexturePath.c_str(), 0, 0, &m_DiffuseSRV, 0));
}

void Quad::initialiseBuffers(ID3D11Device* a_Device)
{
    std::array<Vertex, 4> vertices =
    {
        Vertex(XMVectorSet(-m_Dimensions.x / 2, m_Dimensions.y / 2, 0.0f, 0.0f), XMVectorZero(),
            XMVectorZero(), XMVectorZero()),
        Vertex(XMVectorSet(-m_Dimensions.x / 2, -m_Dimensions.y / 2, 0.0f, 0.0f), XMVectorZero(),
            XMVectorZero(), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)),
        Vertex(XMVectorSet(m_Dimensions.x / 2, -m_Dimensions.y / 2, 0.0f, 0.0f), XMVectorZero(),
            XMVectorZero(), XMVectorSet(1.0f, 1.0f, 0.0f, 0.0f)),
        Vertex(XMVectorSet(m_Dimensions.x / 2, m_Dimensions.y / 2, 0.0f, 0.0f), XMVectorZero(),
            XMVectorZero(), XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f))
    };

    D3D11_BUFFER_DESC vertexBufferDescription
    {
        sizeof(Vertex) * vertices.size(),
        D3D11_USAGE_IMMUTABLE,
        D3D11_BIND_VERTEX_BUFFER,
        0, 0, 0,
    };
    D3D11_SUBRESOURCE_DATA vertexData;
    vertexData.pSysMem = vertices.data();
    HR(a_Device->CreateBuffer(&vertexBufferDescription, &vertexData, &m_VertexBuffer));

    std::array<UINT, 6> indices =
    {
        0u, 1u, 2u, 0u, 2u, 3u
    };

    D3D11_BUFFER_DESC indexBufferDescription =
    {
        sizeof(UINT) * indices.size(),
        D3D11_USAGE_IMMUTABLE,
        D3D11_BIND_INDEX_BUFFER,
        0,
        0,
        0,
    };
    D3D11_SUBRESOURCE_DATA indexData;
    indexData.pSysMem = indices.data();
    HR(a_Device->CreateBuffer(&indexBufferDescription, &indexData, &m_IndexBuffer));
}

void Quad::draw(ID3D11DeviceContext* a_Context, CXMMATRIX a_ViewProjection)
{
    bind(a_Context);
    XMMATRIX mvp = XMMatrixTranslationFromVector(XMLoadFloat3(&m_Position)) * a_ViewProjection;
    m_ShaderMVP->SetMatrix(reinterpret_cast<float*>(&mvp));
    m_ShaderDiffuse->SetResource(m_DiffuseSRV);

    ID3DX11EffectTechnique* technique = m_Shader->GetTechniqueByIndex(0);
    D3DX11_TECHNIQUE_DESC techDesc;
    technique->GetDesc(&techDesc);
    for(UINT p = 0; p < techDesc.Passes; ++p)
    {
        technique->GetPassByIndex(p)->Apply(0, a_Context);
        a_Context->DrawIndexed(6, 0, 0);
    }
}

void Quad::setShader(ID3DX11Effect* a_Shader)
{
    m_Shader = a_Shader;
    m_ShaderMVP = a_Shader->GetVariableByName("gWorldViewProj")->AsMatrix();
    m_ShaderDiffuse = a_Shader->GetVariableByName("gDiffuse")->AsShaderResource();
}

void Quad::bind(ID3D11DeviceContext* a_Context)
{
    auto vertexStride = sizeof(Vertex);
    UINT offset = 0;
    a_Context->IASetVertexBuffers(0, 1, &m_VertexBuffer, &vertexStride, &offset);
    a_Context->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
}
