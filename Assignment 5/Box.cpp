#include <array>

#include "Box.h"
#include "Vertex.h"

Box::Box()
{
}

Box::~Box()
{
    ReleaseCOM(m_VertexBuffer);
}

void Box::setShader(ID3DX11Effect* a_Shader)
{
    m_Shader = a_Shader;
}

void Box::constructVertexBuffer(ID3D11Device* a_Device)
{
    const auto Dimensions = XMFLOAT3(1.0f, 1.0f, 1.0f);

    std::array<Vertex, 36> vertices = 
    {
        //Front plane
        Vertex(XMVectorSet(-Dimensions.x / 2, -Dimensions.y / 2, -Dimensions.z / 2, 0.0f), Colors::White,
            XMVectorZero(), XMVectorZero()),
        Vertex(XMVectorSet(-Dimensions.x / 2, Dimensions.y / 2, -Dimensions.z / 2, 0.0f), Colors::White,
            XMVectorZero(), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)),
        Vertex(XMVectorSet(Dimensions.x / 2, Dimensions.y / 2, -Dimensions.z / 2, 0.0f), Colors::White,
            XMVectorZero(), XMVectorSet(1.0f, 1.0f, 0.0f, 0.0f)),
        Vertex(XMVectorSet(-Dimensions.x / 2, -Dimensions.y / 2, -Dimensions.z / 2, 0.0f), Colors::White,
            XMVectorZero(), XMVectorZero()),
        Vertex(XMVectorSet(Dimensions.x / 2, Dimensions.y / 2, -Dimensions.z / 2, 0.0f), Colors::White,
            XMVectorZero(), XMVectorSet(1.0f, 1.0f, 0.0f, 0.0f)),
        Vertex(XMVectorSet(Dimensions.x / 2, -Dimensions.y / 2, -Dimensions.z / 2, 0.0f), Colors::White,
            XMVectorZero(), XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f)),

        //Left plane
        Vertex(XMVectorSet(-Dimensions.x / 2, -Dimensions.y / 2, -Dimensions.z / 2, 0.0f), Colors::White,
            XMVectorZero(), XMVectorZero()),
        Vertex(XMVectorSet(-Dimensions.x / 2, Dimensions.y / 2, -Dimensions.z / 2, 0.0f), Colors::White,
            XMVectorZero(), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)),
        Vertex(XMVectorSet(-Dimensions.x / 2, Dimensions.y / 2, Dimensions.z / 2, 0.0f), Colors::White,
            XMVectorZero(), XMVectorSet(1.0f, 1.0f, 0.0f, 0.0f)),
        Vertex(XMVectorSet(-Dimensions.x / 2, -Dimensions.y / 2, -Dimensions.z / 2, 0.0f), Colors::White,
            XMVectorZero(), XMVectorZero()),
        Vertex(XMVectorSet(-Dimensions.x / 2, Dimensions.y / 2, Dimensions.z / 2, 0.0f), Colors::White,
            XMVectorZero(), XMVectorSet(1.0f, 1.0f, 0.0f, 0.0f)),
        Vertex(XMVectorSet(-Dimensions.x / 2, -Dimensions.y / 2, Dimensions.z / 2, 0.0f), Colors::White,
            XMVectorZero(), XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f)),

        //Right plane
        Vertex(XMVectorSet(Dimensions.x / 2, -Dimensions.y / 2, -Dimensions.z / 2, 0.0f), Colors::White,
            XMVectorZero(), XMVectorZero()),
        Vertex(XMVectorSet(Dimensions.x / 2, Dimensions.y / 2, -Dimensions.z / 2, 0.0f), Colors::White,
            XMVectorZero(), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)),
        Vertex(XMVectorSet(Dimensions.x / 2, Dimensions.y / 2, Dimensions.z / 2, 0.0f), Colors::White,
            XMVectorZero(), XMVectorSet(1.0f, 1.0f, 0.0f, 0.0f)),
        Vertex(XMVectorSet(Dimensions.x / 2, -Dimensions.y / 2, -Dimensions.z / 2, 0.0f), Colors::White,
            XMVectorZero(), XMVectorZero()),
        Vertex(XMVectorSet(Dimensions.x / 2, Dimensions.y / 2, Dimensions.z / 2, 0.0f), Colors::White,
            XMVectorZero(), XMVectorSet(1.0f, 1.0f, 0.0f, 0.0f)),
        Vertex(XMVectorSet(Dimensions.x / 2, -Dimensions.y / 2, Dimensions.z / 2, 0.0f), Colors::White,
            XMVectorZero(), XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f)),

        //Top plane
        Vertex(XMVectorSet(-Dimensions.x / 2, Dimensions.y / 2, -Dimensions.z / 2, 0.0f), Colors::White,
            XMVectorZero(), XMVectorZero()),
        Vertex(XMVectorSet(Dimensions.x / 2, Dimensions.y / 2, -Dimensions.z / 2, 0.0f), Colors::White,
            XMVectorZero(), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)),
        Vertex(XMVectorSet(-Dimensions.x / 2, Dimensions.y / 2, Dimensions.z / 2, 0.0f), Colors::White,
            XMVectorZero(), XMVectorSet(1.0f, 1.0f, 0.0f, 0.0f)),
        Vertex(XMVectorSet(Dimensions.x / 2, Dimensions.y / 2, -Dimensions.z / 2, 0.0f), Colors::White,
            XMVectorZero(), XMVectorZero()),
        Vertex(XMVectorSet(-Dimensions.x / 2, Dimensions.y / 2, Dimensions.z / 2, 0.0f), Colors::White,
            XMVectorZero(), XMVectorSet(1.0f, 1.0f, 0.0f, 0.0f)),
        Vertex(XMVectorSet(Dimensions.x / 2, Dimensions.y / 2, Dimensions.z / 2, 0.0f), Colors::White,
            XMVectorZero(), XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f)),

        //Bottom plane
        Vertex(XMVectorSet(-Dimensions.x / 2, Dimensions.y / 2, -Dimensions.z / 2, 0.0f), Colors::White,
            XMVectorZero(), XMVectorZero()),
        Vertex(XMVectorSet(Dimensions.x / 2, Dimensions.y / 2, -Dimensions.z / 2, 0.0f), Colors::White,
            XMVectorZero(), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)),
        Vertex(XMVectorSet(-Dimensions.x / 2, Dimensions.y / 2, Dimensions.z / 2, 0.0f), Colors::White,
            XMVectorZero(), XMVectorSet(1.0f, 1.0f, 0.0f, 0.0f)),
        Vertex(XMVectorSet(Dimensions.x / 2, Dimensions.y / 2, -Dimensions.z / 2, 0.0f), Colors::White,
            XMVectorZero(), XMVectorZero()),
        Vertex(XMVectorSet(-Dimensions.x / 2, Dimensions.y / 2, Dimensions.z / 2, 0.0f), Colors::White,
            XMVectorZero(), XMVectorSet(1.0f, 1.0f, 0.0f, 0.0f)),
        Vertex(XMVectorSet(Dimensions.x / 2, Dimensions.y / 2, Dimensions.z / 2, 0.0f), Colors::White,
            XMVectorZero(), XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f)),

        //Rear plane
        Vertex(XMVectorSet(-Dimensions.x / 2, -Dimensions.y / 2, Dimensions.z / 2, 0.0f), Colors::White,
            XMVectorZero(), XMVectorZero()),
        Vertex(XMVectorSet(-Dimensions.x / 2, Dimensions.y / 2, Dimensions.z / 2, 0.0f), Colors::White,
            XMVectorZero(), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)),
        Vertex(XMVectorSet(Dimensions.x / 2, Dimensions.y / 2, Dimensions.z / 2, 0.0f), Colors::White,
            XMVectorZero(), XMVectorSet(1.0f, 1.0f, 0.0f, 0.0f)),
        Vertex(XMVectorSet(-Dimensions.x / 2, -Dimensions.y / 2, Dimensions.z / 2, 0.0f), Colors::White,
            XMVectorZero(), XMVectorZero()),
        Vertex(XMVectorSet(Dimensions.x / 2, Dimensions.y / 2, Dimensions.z / 2, 0.0f), Colors::White,
            XMVectorZero(), XMVectorSet(1.0f, 1.0f, 0.0f, 0.0f)),
        Vertex(XMVectorSet(Dimensions.x / 2, -Dimensions.y / 2, Dimensions.z / 2, 0.0f), Colors::White,
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
}
