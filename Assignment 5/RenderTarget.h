#pragma once
#include <d3dUtil.h>

/// <summary>
/// Represents a RenderTarget to render to, so it can be used as texture 
/// in subsequent rendering phases/steps
/// </summary>
class RenderTarget
{
private:	
	/// <summary>
	/// The viewport of the RenderTarget
	/// </summary>
	D3D11_VIEWPORT m_ViewPort;	
	/// <summary>
	/// The handle to the RenderTarget on the GPU, so it can be bound and rendered to
	/// </summary>
	ID3D11RenderTargetView* m_View = nullptr;	
	/// <summary>
	/// The handle to the shader variable of the RenderTarget, so it can be used as shader variable
	/// </summary>
	ID3D11ShaderResourceView* m_ShaderView = nullptr;	
	/// <summary>
	/// The handle to the texture where this needs to render to
	/// </summary>
	/// <remarks> Mostly stored for deallocation purposes </remarks>
	ID3D11Texture2D* m_TargetTexture = nullptr;

public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="RenderTarget"/> class.
	/// </summary>
	/// <param name="a_Width">Width of the texture to render to </param>
	/// <param name="a_Height">Height of texture to render to </param>
	RenderTarget(float a_Width, float a_Height);
	
	/// <summary>
	/// Finalizes an instance of the <see cref="RenderTarget"/> class and deallocates any attached GPU resources
	/// </summary>
	~RenderTarget();
	
	/// <summary>
	/// Initialises the RenderTarget using the specified ID3D11Device
	/// </summary>
	/// <param name="a_Device">The ID3D11Device to create the resources on </param>
	void initialise(ID3D11Device* a_Device);
	
	/// <summary>
	/// Binds the RenderTarget to the specified DeviceContext, so it can be used to render to
	/// </summary>
	/// <param name="a_Context">The DeviceContext to bind to </param>
	/// <param name="a_DepthStencilView">The DepthStencilView to use alongside the RenderTarget</param>
	void bind(ID3D11DeviceContext* a_Context, ID3D11DepthStencilView* a_DepthStencilView) const;
	
	/// <summary>
	/// Gets the handle to the shader variable to use as texture
	/// </summary>
	/// <returns> The handle to the shader resource </returns>
	ID3D11ShaderResourceView* getResourceView() const;
	
	/// <summary>
	/// Clears the RenderTarget given the bound context and clear color
	/// </summary>
	/// <param name="a_Context">The DeviceContext it is created on </param>
	/// <param name="a_Color"> The color to clear the RenderTarget with </param>
	void clear(ID3D11DeviceContext* a_Context, CXMVECTOR a_Color) const;
private:	
	/// <summary>
	/// Gets the description of the 2D texture needed for initialization of it
	/// </summary>
	/// <returns> The texture description </returns>
	D3D11_TEXTURE2D_DESC getTextureDescription() const;
	
	/// <summary>
	/// Gets description of the RenderTarget to use for creating the RenderTarget itself
	/// </summary>
	/// <returns> The RenderTarget description </returns>
	D3D11_RENDER_TARGET_VIEW_DESC getRenderTargetDescription() const;
	
	/// <summary>
	/// Gets description of the ShaderResourceView to be created alongside the RenderTarget itself,
	/// so it can be used as a texture variable in shaders
	/// </summary>
	/// <returns> The ShaderResourceView description </returns>
	D3D11_SHADER_RESOURCE_VIEW_DESC getResourceViewDescription() const;
};

