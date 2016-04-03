#include "Phone.h"

Phone::Phone()
    : m_RenderTarget(800, 600)
{
    m_Display.setPosition(XMVectorSet(0.0f, 0.0f, -0.051f, 0.0f));
    XMMATRIX cameraOffset = XMMatrixTranslation(0.0f, 0.0f, 0.05f);
    XMStoreFloat4x4(&m_CameraTransform, cameraOffset);
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
    m_RenderTarget.initialise(a_Device);
    m_Box.initialise(a_Device);
    m_Box.constructVertexBuffer(a_Device);
    m_Box.constructIndexBuffer(a_Device);
    m_Display.initialiseBuffers(a_Device);
    m_Display.setTexture(m_RenderTarget.getResourceView());
}

void Phone::draw(ID3D11DeviceContext* a_Context, CXMMATRIX a_ViewProjection)
{
    m_Box.draw(a_Context, a_ViewProjection);
    m_Display.draw(a_Context, a_ViewProjection);
}

void Phone::clearScreen(ID3D11DeviceContext* a_Context, CXMVECTOR a_ClearColor)
{
    m_RenderTarget.clear(a_Context, a_ClearColor);
}

void Phone::setAsRenderTarget(ID3D11DeviceContext* a_Context, ID3D11DepthStencilView* a_DepthStencilView)
{
    m_RenderTarget.bind(a_Context, a_DepthStencilView);
}

XMMATRIX Phone::getCameraTransform() const
{
    return XMLoadFloat4x4(&m_CameraTransform);
}
