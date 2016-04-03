#include "RenderTarget.h"


RenderTarget::RenderTarget(float a_Width, float a_Height)
{
    m_ViewPort.TopLeftX = 0.0f;
    m_ViewPort.TopLeftY = 0.0f;
    m_ViewPort.Width = a_Width;
    m_ViewPort.Height = a_Height;
    m_ViewPort.MinDepth = 0.0f;
    m_ViewPort.MaxDepth = 1.0f;
}

RenderTarget::~RenderTarget()
{
    ReleaseCOM(m_ShaderView);
    ReleaseCOM(m_TargetTexture);
    //ReleaseCOM(m_View);
}

void RenderTarget::initialise(ID3D11Device* a_Device)
{
    D3D11_TEXTURE2D_DESC textureDescription = getTextureDescription();
    HR(a_Device->CreateTexture2D(&textureDescription, nullptr, &m_TargetTexture));
    D3D11_RENDER_TARGET_VIEW_DESC renderTargetDescription = getRenderTargetDescription();
    HR(a_Device->CreateRenderTargetView(m_TargetTexture, &renderTargetDescription,
        &m_View));
    D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceView = getResourceViewDescription();
    HR(a_Device->CreateShaderResourceView(m_TargetTexture, &shaderResourceView, &m_ShaderView));
}

void RenderTarget::bind(ID3D11DeviceContext* a_Context, ID3D11DepthStencilView* a_DepthStencilView)
{
    a_Context->RSSetViewports(1, &m_ViewPort);
    a_Context->OMSetRenderTargets(1, &m_View, a_DepthStencilView);
}

ID3D11ShaderResourceView* RenderTarget::getResourceView() const
{
    return m_ShaderView;
}

void RenderTarget::clear(ID3D11DeviceContext* a_Context, CXMVECTOR a_Color)
{
    XMFLOAT4 color;
    XMStoreFloat4(&color, a_Color);
    a_Context->ClearRenderTargetView(m_View, reinterpret_cast<float*>(&color));
}

D3D11_TEXTURE2D_DESC RenderTarget::getTextureDescription() const
{
    D3D11_TEXTURE2D_DESC textureDescription;
    textureDescription.Width = static_cast<UINT>(m_ViewPort.Width);
    textureDescription.Height = static_cast<UINT>(m_ViewPort.Height);
    textureDescription.MipLevels = 1;
    textureDescription.ArraySize = 1;
    textureDescription.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
    textureDescription.SampleDesc.Count = 1;
    textureDescription.SampleDesc.Quality = 0;
    textureDescription.Usage = D3D11_USAGE_DEFAULT;
    textureDescription.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
    textureDescription.CPUAccessFlags = 0;
    textureDescription.MiscFlags = 0;
    return textureDescription;
}

D3D11_RENDER_TARGET_VIEW_DESC RenderTarget::getRenderTargetDescription() const
{
    D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDescription;
    renderTargetViewDescription.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
    renderTargetViewDescription.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
    renderTargetViewDescription.Texture2D.MipSlice = 0;
    return renderTargetViewDescription;
}

D3D11_SHADER_RESOURCE_VIEW_DESC RenderTarget::getResourceViewDescription() const
{
    D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDescription;
    shaderResourceViewDescription.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
    shaderResourceViewDescription.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    shaderResourceViewDescription.Texture2D.MostDetailedMip = 0;
    shaderResourceViewDescription.Texture2D.MipLevels = 1;
    return shaderResourceViewDescription;
}
