#include <array>

#include <Vertex.h>

#include "Quad.h"

Quad::Quad()
{
    setPosition(XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f));
}

Quad::~Quad()
{
    ReleaseCOM(m_Shader);
}

void Quad::bind(ID3D11DeviceContext* a_Context)
{
    auto vertexStride = sizeof(Vertex);
    UINT offset = 0;
    a_Context->IASetVertexBuffers(0, 1, &m_VertexBuffer, &vertexStride, &offset);
    a_Context->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
}

void Quad::setShader(ID3DX11Effect* a_Shader)
{
    m_Shader = a_Shader;
    m_ShaderMVP = a_Shader->GetVariableByName("gWorldViewProj")->AsMatrix();
    m_ShaderTime = a_Shader->GetVariableByName("gTime")->AsScalar();
}

void Quad::setPosition(CXMVECTOR a_Position)
{
    XMMATRIX transform = XMMatrixTranslationFromVector(a_Position);
    XMStoreFloat4x4(&m_Transform, transform);
}

void Quad::update(float a_DeltaTime)
{
    m_TimePassed += a_DeltaTime;
}

void Quad::draw(ID3D11DeviceContext* a_Context, CXMMATRIX a_ViewProjection)
{
    bind(a_Context);
    XMMATRIX modelViewProjection = XMLoadFloat4x4(&m_Transform) * a_ViewProjection;
    m_ShaderMVP->SetMatrix(reinterpret_cast<float*>(&modelViewProjection));
    m_ShaderTime->SetFloat(m_TimePassed);

    ID3DX11EffectTechnique* technique = m_Shader->GetTechniqueByIndex(0);
    D3DX11_TECHNIQUE_DESC techDesc;
    technique->GetDesc(&techDesc);
    for(UINT p = 0; p < techDesc.Passes; ++p)
    {
        technique->GetPassByIndex(p)->Apply(0, a_Context);
        a_Context->DrawIndexed(6, 0, 0);
    }
}

void Quad::initialiseBuffers(ID3D11Device* a_Device)
{
    const float Size = 5.0f;
    std::array<Vertex, 4> vertices =
    {
        Vertex(XMVectorSet(-Size / 2, -Size / 2, 0.0f, 0.0f), XMVectorZero()),
        Vertex(XMVectorSet(-Size / 2, Size / 2, 0.0f, 0.0f), XMVectorZero()),
        Vertex(XMVectorSet(Size / 2, Size / 2, 0.0f, 0.0f), XMVectorZero()),
        Vertex(XMVectorSet(Size / 2, -Size / 2, 0.0f, 0.0f), XMVectorZero())
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