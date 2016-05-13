#include <array>

#include "Box.h"
#include "Vertex.h"

Box::Box(XMVECTOR a_Dimensions, const std::wstring& a_TexturePath)
    : m_TexturePath(a_TexturePath)
{
    XMStoreFloat3(&m_Dimensions, a_Dimensions);
    auto identity = XMMatrixIdentity();
    XMStoreFloat4x4(&m_Transform, identity);
}

Box::~Box()
{
    ReleaseCOM(m_VertexBuffer);
    ReleaseCOM(m_DiffuseSRV);
    ReleaseCOM(m_IndexBuffer);
}

void Box::setTransform(CXMMATRIX a_Transform)
{
    XMStoreFloat4x4(&m_Transform, a_Transform);
}

void Box::initialise(ID3D11Device* a_Device)
{
    HR(D3DX11CreateShaderResourceViewFromFile(a_Device, m_TexturePath.c_str(), 0, 0, &m_DiffuseSRV, 0));
}

void Box::setShader(ID3DX11Effect* a_Shader)
{
    m_Shader = a_Shader;
    m_ShaderMVP = a_Shader->GetVariableByName("gWorldViewProj")->AsMatrix();
    m_ShaderDiffuse = a_Shader->GetVariableByName("gDiffuse")->AsShaderResource();
}

void Box::draw(ID3D11DeviceContext* a_Context, CXMMATRIX a_ViewProjection)
{
    bind(a_Context);
    XMMATRIX mvp = XMLoadFloat4x4(&m_Transform) * a_ViewProjection;
    m_ShaderMVP->SetMatrix(reinterpret_cast<float*>(&mvp));
    m_ShaderDiffuse->SetResource(m_DiffuseSRV);

    ID3DX11EffectTechnique* technique = m_Shader->GetTechniqueByIndex(0);
    D3DX11_TECHNIQUE_DESC techDesc;
    technique->GetDesc(&techDesc);

    for(UINT p = 0; p < techDesc.Passes; ++p)
    {
        technique->GetPassByIndex(p)->Apply(0, a_Context);
        a_Context->DrawIndexed(36, 0, 0);
    }
}

void Box::constructVertexBuffer(ID3D11Device* a_Device)
{
    std::array<Vertex, 24> vertices = 
    {
        //Front plane
        Vertex(XMVectorSet(-m_Dimensions.x / 2, -m_Dimensions.y / 2, -m_Dimensions.z / 2, 0.0f), Colors::White),
        Vertex(XMVectorSet(-m_Dimensions.x / 2, m_Dimensions.y / 2, -m_Dimensions.z / 2, 0.0f), Colors::White),
        Vertex(XMVectorSet(m_Dimensions.x / 2, m_Dimensions.y / 2, -m_Dimensions.z / 2, 0.0f), Colors::White),
        Vertex(XMVectorSet(m_Dimensions.x / 2, -m_Dimensions.y / 2, -m_Dimensions.z / 2, 0.0f), Colors::White),

        //Rear plane
        Vertex(XMVectorSet(-m_Dimensions.x / 2, -m_Dimensions.y / 2, m_Dimensions.z / 2, 0.0f), Colors::White),
        Vertex(XMVectorSet(-m_Dimensions.x / 2, m_Dimensions.y / 2, m_Dimensions.z / 2, 0.0f), Colors::White),
        Vertex(XMVectorSet(m_Dimensions.x / 2, m_Dimensions.y / 2, m_Dimensions.z / 2, 0.0f), Colors::White),
        Vertex(XMVectorSet(m_Dimensions.x / 2, -m_Dimensions.y / 2, m_Dimensions.z / 2, 0.0f), Colors::White),

        //Left plane
        Vertex(XMVectorSet(-m_Dimensions.x / 2, -m_Dimensions.y / 2, m_Dimensions.z / 2, 0.0f), Colors::White),
        Vertex(XMVectorSet(-m_Dimensions.x / 2, m_Dimensions.y / 2, m_Dimensions.z / 2, 0.0f), Colors::White),
        Vertex(XMVectorSet(-m_Dimensions.x / 2, m_Dimensions.y / 2, -m_Dimensions.z / 2, 0.0f), Colors::White),
        Vertex(XMVectorSet(-m_Dimensions.x / 2, -m_Dimensions.y / 2, -m_Dimensions.z / 2, 0.0f), Colors::White),

        //Right plane
        Vertex(XMVectorSet(m_Dimensions.x / 2, -m_Dimensions.y / 2, -m_Dimensions.z / 2, 0.0f), Colors::White),
        Vertex(XMVectorSet(m_Dimensions.x / 2, m_Dimensions.y / 2, -m_Dimensions.z / 2, 0.0f), Colors::White),
        Vertex(XMVectorSet(m_Dimensions.x / 2, m_Dimensions.y / 2, m_Dimensions.z / 2, 0.0f), Colors::White),
        Vertex(XMVectorSet(m_Dimensions.x / 2, -m_Dimensions.y / 2, m_Dimensions.z / 2, 0.0f), Colors::White),

        //Top plane
        Vertex(XMVectorSet(-m_Dimensions.x / 2, m_Dimensions.y / 2, -m_Dimensions.z / 2, 0.0f), Colors::White),
        Vertex(XMVectorSet(-m_Dimensions.x / 2, m_Dimensions.y / 2, m_Dimensions.z / 2, 0.0f), Colors::White),
        Vertex(XMVectorSet(m_Dimensions.x / 2, m_Dimensions.y / 2, m_Dimensions.z / 2, 0.0f), Colors::White),
        Vertex(XMVectorSet(m_Dimensions.x / 2, m_Dimensions.y / 2, -m_Dimensions.z / 2, 0.0f), Colors::White),

        //Bottom plane
        Vertex(XMVectorSet(-m_Dimensions.x / 2, -m_Dimensions.y / 2, -m_Dimensions.z / 2, 0.0f), Colors::White),
        Vertex(XMVectorSet(-m_Dimensions.x / 2, -m_Dimensions.y / 2, m_Dimensions.z / 2, 0.0f), Colors::White),
        Vertex(XMVectorSet(m_Dimensions.x / 2, -m_Dimensions.y / 2, m_Dimensions.z / 2, 0.0f), Colors::White),
        Vertex(XMVectorSet(m_Dimensions.x / 2, -m_Dimensions.y / 2, -m_Dimensions.z / 2, 0.0f), Colors::White),
    };

    auto currentFace = 1u;
    const auto TotalFaces = 6u;
    const auto OffsetPerFace = 1.0f / TotalFaces;
    for(unsigned int i = 0; i < vertices.size(); )
    {
        const float CurrentFaceOffset = OffsetPerFace * currentFace;
        vertices[i++].UVCoordinates = XMFLOAT2(CurrentFaceOffset - OffsetPerFace, 1.0f);
        vertices[i++].UVCoordinates = XMFLOAT2(CurrentFaceOffset - OffsetPerFace, 0.0f);
        vertices[i++].UVCoordinates = XMFLOAT2(CurrentFaceOffset, 0.0f);
        vertices[i++].UVCoordinates = XMFLOAT2(CurrentFaceOffset, 1.0f);
        currentFace++;
    }

    D3D11_BUFFER_DESC vertexBufferDescription
    {
        sizeof(Vertex) * vertices.size(),
        D3D11_USAGE_IMMUTABLE,
        D3D11_BIND_VERTEX_BUFFER,
        0, 0, 0
    };
    D3D11_SUBRESOURCE_DATA vertexData;
    vertexData.pSysMem = vertices.data();
    HR(a_Device->CreateBuffer(&vertexBufferDescription, &vertexData, &m_VertexBuffer));
}

void Box::constructIndexBuffer(ID3D11Device* a_Device)
{
    std::array<UINT, 36> indices;
    const auto VerticesPerQuad = 4u;
    auto currentIndex = 0u;
    for(int i = 0; i < 6; i++)
    {
        const auto CurrentOffset = VerticesPerQuad * i;
        indices[currentIndex++] = 0u + CurrentOffset;
        indices[currentIndex++] = 1u + CurrentOffset;
        indices[currentIndex++] = 2u + CurrentOffset;
        indices[currentIndex++] = 0u + CurrentOffset;
        indices[currentIndex++] = 2u + CurrentOffset;
        indices[currentIndex++] = 3u + CurrentOffset;
    }

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

void Box::bind(ID3D11DeviceContext * a_Context) const
{
    auto vertexStride = sizeof(Vertex);
    UINT offset = 0;
    a_Context->IASetVertexBuffers(0, 1, &m_VertexBuffer, &vertexStride, &offset);
    a_Context->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
}