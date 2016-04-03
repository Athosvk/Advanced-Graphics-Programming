#include "Phone.h"

Phone::Phone()
{
}

Phone::~Phone()
{
    ReleaseCOM(m_Shader);
}

void Phone::setShader(ID3DX11Effect* a_Shader)
{
    m_Shader = a_Shader;
    m_Box.setShader(a_Shader);
    m_Display.setShader(a_Shader);
}

void Phone::initialise(ID3D11Device* a_Device)
{
    m_Box.initialise(a_Device);
    m_Box.constructVertexBuffer(a_Device);
    m_Box.constructIndexBuffer(a_Device);
    m_Display.initialise(a_Device);
    m_Display.initialiseBuffers(a_Device);
}

void Phone::draw(ID3D11DeviceContext* a_Context, CXMMATRIX a_ViewProjection)
{
    //m_Box.draw(a_Context, a_ViewProjection);
    m_Display.draw(a_Context, a_ViewProjection);
}
