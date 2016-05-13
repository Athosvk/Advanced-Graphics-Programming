#pragma once
#include "Box.h"
#include "Quad.h"
#include "RenderTarget.h"

/// <summary>
/// Represents the combination of a quad and a box to render a phone with a display
/// </summary>
class Phone
{
private:	
	/// <summary>
	/// The box, representing the phone itself
	/// </summary>
	Box m_Box = Box(XMVectorSet(0.4f, 1.0f, 0.1f, 0.0f), L"Assets/Textures/Phone.png");
	/// <summary>
	/// The shader to use for rendering the phone
	/// </summary>
	ID3DX11Effect* m_Shader;
	/// <summary>
	/// The quad to use for the display of the phone
	/// </summary>
	Quad m_Display = Quad(XMVectorSet(0.32f, 0.7f, 0.0f, 0.0f), L"Assets/Textures/Display.png");    
	/// <summary>
	/// The transform/origin of the camera to render the display from
	/// </summary>
	XMFLOAT4X4 m_CameraTransform;	
	/// <summary>
	/// The render target to render to for rendering the display for the phone
	/// </summary>
	RenderTarget m_RenderTarget;

public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="Phone"/> class.
	/// </summary>
	Phone();

	/// <summary>
	/// Finalizes an instance of the <see cref="Phone"/> class as well as deallocating the used shader
	/// </summary>
	~Phone();
	
	/// <summary>
	/// Sets the shader to use by the phone
	/// </summary>
	/// <param name="a_Shader">The handle to the shader </param>
	void setShader(ID3DX11Effect* a_Shader);
	
	/// <summary>
	/// Initialises the phone using the given Direct3D11 device
	/// </summary>
	/// <param name="a_Device">The Direct3D device to construct the buffers on</param>
	void initialise(ID3D11Device* a_Device);
	
	/// <summary>
	/// Draws the phone using the given context
	/// </summary>
	/// <param name="a_Context">The context to draw with </param>
	/// <param name="a_ViewProjection">The view projection matrix of the camera </param>
	void draw(ID3D11DeviceContext* a_Context, CXMMATRIX a_ViewProjection);
	
	/// <summary>
	/// Clears the screen of the phone, i.e. the quad, to prevent artifacts from overlapping rendering
	/// </summary>
	/// <param name="a_Context">The context to clear the texture with </param>
	/// <param name="a_ClearColor"> The color to clear the texture with </param>
	void clearScreen(ID3D11DeviceContext* a_Context, CXMVECTOR a_ClearColor);
	
	/// <summary>
	/// Sets the phone ('s screen) as the current render target, so the scene can be rendered to it
	/// </summary>
	/// <param name="a_Context">The context to bind the render target to </param>
	/// <param name="a_DepthStencilView">The depth stencil view to use alongside the texture </param>
	void setAsRenderTarget(ID3D11DeviceContext* a_Context, ID3D11DepthStencilView* a_DepthStencilView);
    	
	/// <summary>
	/// Resizes the texture used for the screen of the phone, so the dimensions keep up to date with the render target dimensions
	/// </summary>
	/// <param name="a_Dimensions">The new dimensions of the screen</param>
	/// <param name="a_Device">The device to re-initialize the render target with </param>
	void resizeScreen(XMFLOAT2 a_Dimensions, ID3D11Device* a_Device);
	
	/// <summary>
	/// Gets the transform of the camera of the phone, to set the view transform of the scene with
	/// </summary>
	/// <returns> The transform of the camera of the phone </returns>
	XMMATRIX getCameraTransform() const;
};

