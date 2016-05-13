#pragma once
#include <d3dUtil.h>

/// <summary>
/// Represents a simple, non-uniform sized, box
/// </summary>
class Box
{
private:	
	/// <summary>
	/// The vertex buffer handle to bind for the rendering phase
	/// </summary>
	ID3D11Buffer* m_VertexBuffer = nullptr;	
	/// <summary>
	/// The index buffer handle to bind for the rendering phase
	/// </summary>
	ID3D11Buffer* m_IndexBuffer = nullptr;	
	/// <summary>
	/// The shader to use for rendering the box
	/// </summary>
	ID3DX11Effect* m_Shader = nullptr;	
	/// <summary>
	/// The handle to the Transform/MVP matrix in the shader, of which a handle is stored
	/// in the m_Shader variable
	/// </summary>
	/// <remarks> Used to update the screen position of the box before rendering </remarks>
	ID3DX11EffectMatrixVariable* m_ShaderMVP = nullptr;	
	/// <summary>
	/// The handle to the allocated buffer of the texture used for this box
	/// </summary>
	ID3DX11EffectShaderResourceVariable* m_ShaderDiffuse = nullptr;	
	/// <summary>
	/// The resouce view to the texture used by the shader
	/// </summary>
	ID3D11ShaderResourceView* m_DiffuseSRV = nullptr;	
	/// <summary>
	/// The dimensions of the box
	/// </summary>
	XMFLOAT3 m_Dimensions;	
	/// <summary>
	/// The path to the texture to be used for this box
	/// </summary>
	/// <remarks> Stored since initialization of the texture needs to be delayed </remarks>
	std::wstring m_TexturePath;	
	/// <summary>
	/// The world space transform (matrix) of this box
	/// </summary>
	XMFLOAT4X4 m_Transform;

public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="Box"/> class. Requires a call to initialise.
	/// </summary>
	/// <param name="a_Dimensions">The dimensions of the box </param>
	/// <param name="a_TexturePath">The path to the texture to be used by the box</param>
	Box(XMVECTOR a_Dimensions, const std::wstring& a_TexturePath);
	
	/// <summary>
	/// Finalizes an instance of the <see cref="Box"/> class and deallocates attached texture and buffers
	/// </summary>
	~Box();
	
	/// <summary>
	/// Sets the world transform of the box, so it can move at runtime
	/// </summary>
	/// <param name="a_Transform">The new transform </param>
	void setTransform(CXMMATRIX a_Transform);
	
	/// <summary>
	/// Initialises the box using the specified Direct3D device for initialization
	/// </summary>
	/// <remarks> Used since the given Assignment class needs to run initialize first </remarks>
	/// <param name="a_Device">The a_ device.</param>
	void initialise(ID3D11Device* a_Device);
	
	/// <summary>
	/// Sets the shader to be used for rendering the box 
	/// </summary>
	/// <param name="a_Shader">The handle to the shader to use </param>
	void setShader(ID3DX11Effect* a_Shader);
	
	/// <summary>
	/// Draws the box given the specified context 
	/// </summary>
	/// <param name="a_Context"> The contexxt to use for rendering </param>
	/// <param name="a_ViewProjection">The view-projection matrix of the camera </param>
	void draw(ID3D11DeviceContext* a_Context, CXMMATRIX a_ViewProjection);
	
	/// <summary>
	/// Constructs the vertex buffer using the given Direct3D11 device
	/// </summary>
	/// <param name="a_Device">The Direct3D device to construct the vertex buffer on </param>
	void constructVertexBuffer(ID3D11Device* a_Device);
	
	/// <summary>
	/// Constructs the index buffer using the given Direct3D11 device
	/// </summary>
	/// <param name="a_Device">The Direct3D device to construct the index buffer on </param>
	void constructIndexBuffer(ID3D11Device* a_Device);
private:	
	/// <summary>
	/// Binds the buffers to the specified device context
	/// </summary>
	/// <param name="a_Context">The context to bind to </param>
	void bind(ID3D11DeviceContext* a_Context) const;
};

