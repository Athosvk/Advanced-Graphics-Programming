#pragma once
#include <assimp/vector2.h>
#include <assimp/vector3.h>
#include <vector>
#include <d3d11.h>

#include "Vertex.h"

class Mesh
{
private:
    std::vector<Vertex> m_Vertices;
    std::vector<UINT> m_Indices;
    ID3D11Buffer* m_VertexBuffer;
    ID3D11Buffer* m_IndexBuffer;

public:
    Mesh(const std::string& a_Filepath, ID3D11Device* a_Device);
    ~Mesh();

    void draw(ID3D11DeviceContext* a_Contex);
    void bind(ID3D11DeviceContext* a_Context);
private:
    XMFLOAT3 toXMFloat3(aiVector3D a_Vector);
    void loadMeshdata(const std::string& a_Filepath);
    void buildIndexBuffer(ID3D11Device* a_Device);
    void buildVertexBuffer(ID3D11Device* a_Device);
};
