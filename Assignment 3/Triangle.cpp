#include <array>

#include "Triangle.h"

Triangle::Triangle(float a_Size, XMVECTOR a_Color)
{
    XMStoreFloat4(&m_Color, a_Color);
    XMStoreFloat4x4(&m_Transform, XMMatrixScaling(15.0f, 15.0f, 15.0f));
    setPosition(XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f));
}

Triangle::~Triangle()
{
    ReleaseCOM(m_IndexBuffer);
    ReleaseCOM(m_VertexBuffer);
}

void Triangle::bind(ID3D11DeviceContext* a_Context)
{
    auto vertexStride = sizeof(Vertex);
    UINT offset = 0;
    a_Context->IASetVertexBuffers(0, 1, &m_VertexBuffer, &vertexStride, &offset);
    a_Context->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
}

void Triangle::setShader(ID3DX11Effect* a_Shader)
{
    m_Shader = a_Shader;
    m_ShaderMVP = a_Shader->GetVariableByName("gWorldViewProj")->AsMatrix();
}

void Triangle::setPosition(CXMVECTOR a_Position)
{
    XMMATRIX transform = XMMatrixTranslationFromVector(a_Position);
    XMStoreFloat4x4(&m_Transform, transform);
}

void Triangle::draw(ID3D11DeviceContext* a_Context, CXMMATRIX a_ViewProjection)
{
    bind(a_Context);
    XMMATRIX modelViewProjection = XMLoadFloat4x4(&m_Transform) * a_ViewProjection;
    m_ShaderMVP->SetMatrix(reinterpret_cast<float*>(&modelViewProjection));

    ID3DX11EffectTechnique* technique = m_Shader->GetTechniqueByIndex(0);
    D3DX11_TECHNIQUE_DESC techDesc;
    technique->GetDesc(&techDesc);
    for(UINT p = 0; p < techDesc.Passes; ++p)
    {
        technique->GetPassByIndex(p)->Apply(0, a_Context);
        a_Context->Draw(3, 0);
    }
}

void Triangle::initialiseBuffers(ID3D11Device* a_Device)
{
    std::array<Vertex, 3> vertices = 
    { 
        Vertex(XMFLOAT3(-0.5f, 0.0f, 0.0f), m_Color),
        Vertex(XMFLOAT3(0.0f, 1.0f, 0.0f), m_Color),
        Vertex(XMFLOAT3(0.5f, 0.0f, 0.0f), m_Color)
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

    std::array<UINT, 3> indices =
    {
        0u, 1u, 2u
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
