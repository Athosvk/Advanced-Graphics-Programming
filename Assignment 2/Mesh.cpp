#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <d3dUtil.h>

#include "Mesh.h"

Mesh::Mesh(const std::string& a_Filepath, ID3D11Device* a_Device)
{
    loadMeshdata(a_Filepath);
    buildVertexBuffer(a_Device);
    buildIndexBuffer(a_Device);
}

Mesh::~Mesh()
{
    ReleaseCOM(m_VertexBuffer);
    ReleaseCOM(m_IndexBuffer);
}

void Mesh::draw(ID3D11DeviceContext* a_Context)
{
    a_Context->DrawIndexed(m_Indices.size(), 0, 0);
}

void Mesh::bind(ID3D11DeviceContext* a_Context)
{
    a_Context->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
    auto vertexStride = sizeof(Vertex);
    UINT offset = 0;
    a_Context->IASetVertexBuffers(0, 1, &m_VertexBuffer, &vertexStride, &offset);
}

XMFLOAT3 Mesh::toXMFloat3(aiVector3D a_Vector)
{
    return XMFLOAT3(a_Vector.x, a_Vector.y, a_Vector.z);
}

void Mesh::loadMeshdata(const std::string& a_Filepath)
{
    Assimp::Importer importer;
    const auto scene = importer.ReadFile(a_Filepath, aiPostProcessSteps::aiProcess_CalcTangentSpace |
        aiPostProcessSteps::aiProcess_Triangulate |
        aiPostProcessSteps::aiProcess_JoinIdenticalVertices |
        aiPostProcessSteps::aiProcess_SortByPType);
    auto error = importer.GetErrorString();
    auto mesh = scene->mMeshes[0];

    m_Vertices.reserve(mesh->mNumVertices);
    for(auto i = 0u; i < mesh->mNumVertices; i++)
    {
        m_Vertices.emplace_back(toXMFloat3(mesh->mVertices[i]));
    }
    m_Indices.reserve(mesh->mNumFaces * 3);
    for(auto i = 0u; i < mesh->mNumFaces; ++i)
    {
        aiFace currentFace = mesh->mFaces[i];
        for(auto j = 0u; j < currentFace.mNumIndices; ++j)
        {
            m_Indices.push_back(currentFace.mIndices[j]);
        }
    }
}

void Mesh::buildVertexBuffer(ID3D11Device* a_Device)
{
    D3D11_BUFFER_DESC vertexBufferDescription
    {
        sizeof(Vertex) * m_Vertices.size(),
        D3D11_USAGE_IMMUTABLE,
        D3D11_BIND_VERTEX_BUFFER,
        0,
        0,
        0,
    };
    D3D11_SUBRESOURCE_DATA vertexData;
    vertexData.pSysMem = m_Vertices.data();
    HR(a_Device->CreateBuffer(&vertexBufferDescription, &vertexData, &m_VertexBuffer));
}

void Mesh::buildIndexBuffer(ID3D11Device* a_Device)
{
    D3D11_BUFFER_DESC indexBufferDescription =
    {
        sizeof(UINT) * m_Indices.size(),
        D3D11_USAGE_IMMUTABLE,
        D3D11_BIND_INDEX_BUFFER,
        0,
        0,
        0,
    };
    D3D11_SUBRESOURCE_DATA indexData;
    indexData.pSysMem = m_Indices.data();
    HR(a_Device->CreateBuffer(&indexBufferDescription, &indexData, &m_IndexBuffer));
}
