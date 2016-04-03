#include <array>

#include "Box.h"
#include "Vertex.h"

Box::Box()
{

}

Box::~Box()
{
    ReleaseCOM(m_VertexBuffer);
    ReleaseCOM(m_DiffuseSRV);
    ReleaseCOM(m_Shader);
}

void Box::initialise(ID3D11Device * a_Device)
{
    HR(D3DX11CreateShaderResourceViewFromFile(a_Device,
        L"Assets/Textures/Dice.png", 0, 0, &m_DiffuseSRV, 0));
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
    XMMATRIX mvp = a_ViewProjection;
    m_ShaderMVP->SetMatrix(reinterpret_cast<float*>(&mvp));
    m_ShaderDiffuse->SetResource(m_DiffuseSRV);

    ID3DX11EffectTechnique* technique = m_Shader->GetTechniqueByIndex(0);
    D3DX11_TECHNIQUE_DESC techDesc;
    technique->GetDesc(&techDesc);
    for(UINT p = 0; p < techDesc.Passes; ++p)
    {
        technique->GetPassByIndex(p)->Apply(0, a_Context);
        a_Context->Draw(36, 0);
    }
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
        0, 0, 0
    };
    D3D11_SUBRESOURCE_DATA vertexData;
    vertexData.pSysMem = vertices.data();
    HR(a_Device->CreateBuffer(&vertexBufferDescription, &vertexData, &m_VertexBuffer));
}

void Box::bind(ID3D11DeviceContext * a_Context)
{
    auto vertexStride = sizeof(Vertex);
    UINT offset = 0;
    a_Context->IASetVertexBuffers(0, 1, &m_VertexBuffer, &vertexStride, &offset);
}
