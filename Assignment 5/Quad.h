#pragma once
#include <d3dUtil.h>

/// <summary>
/// Represents a single quad to use as display for the rendered phone
/// </summary>
class Quad
{
private:	
	/// <summary>
	/// The shader to use for when rendering the quad
	/// </summary>
	ID3DX11Effect* m_Shader = nullptr;
	/// <summary>
	/// The handle to the vertex buffer to use for rendering the quad
	/// </summary>
	ID3D11Buffer* m_VertexBuffer = nullptr;
	/// <summary>
	/// The handle to the index buffer to use for rendering the quad
	/// </summary>
	ID3D11Buffer* m_IndexBuffer = nullptr;
	/// <summary>
	/// The handle to the MVP/trasnform matrix in the shader, so that the screen position can be 
	/// updated
	/// </summary>
	ID3DX11EffectMatrixVariable* m_ShaderMVP = nullptr;	
	/// <summary>
	/// The handle to the allocated texture on the GPU, so we can bind it for rendering
	/// </summary>
	ID3DX11EffectShaderResourceVariable* m_ShaderDiffuse = nullptr;
	/// <summary>
	/// The handle to the texture variable in the shader, so we can bind a custom texture to it
	/// </summary>
	ID3D11ShaderResourceView* m_DiffuseSRV = nullptr;	
	/// <summary>
	/// The dimensions of the quad
	/// </summary>
	XMFLOAT2 m_Dimensions;	
	/// <summary>
	/// The path to the texture to be used by this quad, if applicable
	/// </summary>
	/// <remarks> Stored because initialization is delayed by the matching Assignment class </remarks>
	std::wstring m_TexturePath;	
	/// <summary>
	/// The position of the quad in world space coordinates
	/// </summary>
	XMFLOAT3 m_Position;

public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="Quad"/> class.
	/// </summary>
	/// <param name="a_Dimensions">The dimensions of the quad </param>
	/// <param name="a_TexturePath">The path to the texture to be used by the quad </param>
	Quad(CXMVECTOR a_Dimensions, const std::wstring& a_TexturePath);	
	/// <summary>
	/// Finalizes an instance of the <see cref="Quad"/> class and deallocates any used GPU resources
	/// </summary>
	~Quad();
	
	/// <summary>
	/// Sets the position of the quad in world space coordinates
	/// </summary>
	/// <param name="a_Position">The new position</param>
	void setPosition(CXMVECTOR a_Position);
	
	/// <summary>
	/// Sets the texture to be used by the quad and deallocates the previous if needed
	/// </summary>
	/// <param name="a_Texture"> The shader resoruce view to the texture </param>
	void setTexture(ID3D11ShaderResourceView* a_Texture);	

	/// <summary>
	/// Initialises the specified a_ device.
	/// </summary>
	/// <param name="a_Device">The a_ device.</param>
	void initialise(ID3D11Device* a_Device);
	
	/// <summary>
	/// Initialises the buffers to be used by the quad
	/// </summary>
	/// <param name="a_Device">The D3D11Device to create the buffers on </param>
	void initialiseBuffers(ID3D11Device* a_Device);
	
	/// <summary>
	/// Draws the quad using the given DeviceContext
	/// </summary>
	/// <param name="a_Context">The DeviceContext to render with </param>
	/// <param name="a_ViewProjection">The view-projection matrix used to draw </param>
	void draw(ID3D11DeviceContext* a_Context, CXMMATRIX a_ViewProjection);
	
	/// <summary>
	/// Sets the shader to render the quad and searches for the necessary constant buffers in the shader
	/// </summary>
	/// <param name="a_Shader">The resource handle to the new shader </param>
	void setShader(ID3DX11Effect* a_Shader);
private:	
	/// <summary>
	/// Binds the buffers of the quad to the given DeviceContext, so they can be used for rendering
	/// </summary>
	/// <param name="a_Context">The ID3D11DeviceContext to bind to </param>
	void bind(ID3D11DeviceContext* a_Context) const;
};