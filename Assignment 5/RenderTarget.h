#pragma once
#include <d3dUtil.h>

class RenderTarget
{
private:
    D3D11_VIEWPORT m_ViewPort;
    ID3D11RenderTargetView* m_View = nullptr;
    ID3D11ShaderResourceView* m_ShaderView = nullptr;
    ID3D11Texture2D* m_TargetTexture = nullptr;

public:
    RenderTarget(float a_Width, float a_Height);
    ~RenderTarget();

    void initialise(ID3D11Device* a_Device);
    void bind(ID3D11DeviceContext* a_Context, ID3D11DepthStencilView* a_DepthStencilView);
    ID3D11ShaderResourceView* getResourceView() const;
    void clear(ID3D11DeviceContext* a_Context, CXMVECTOR a_Color);
private:
    D3D11_TEXTURE2D_DESC getTextureDescription() const;
    D3D11_RENDER_TARGET_VIEW_DESC getRenderTargetDescription() const;
    D3D11_SHADER_RESOURCE_VIEW_DESC getResourceViewDescription() const;
};

