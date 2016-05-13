#pragma once
#include <d3dUtil.h>
#include <Vertex.h>

/// <summary>
/// Represents a simple equilateral triangle
/// </summary>
class Triangle
{
private:	
	/// <summary>
	/// The color of the triangle, used to specify the color of the vertices
	/// </summary>
	XMFLOAT4 m_Color;
	/// <summary>
	/// The shader this triangle should be rendered with
	/// </summary>
	ID3DX11Effect* m_Shader = nullptr;	
	/// <summary>
	/// The world transform of the triangle
	/// </summary>
	XMFLOAT4X4 m_Transform;	
	/// <summary>
	/// The handle to the index buffer of this triangle, to bind it for rendering
	/// </summary>
	ID3D11Buffer* m_IndexBuffer = nullptr;	
	/// <summary>
	/// The handle to the vertex buffer of this triangle, to bind it for rendering
	/// </summary>
	ID3D11Buffer* m_VertexBuffer = nullptr;	
	/// <summary>
	/// The handle to the transform/model view projection matrix in the shader, so 
	/// it can be updated before the rendering phase
	/// </summary>
	ID3DX11EffectMatrixVariable* m_ShaderMVP;

public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="Triangle"/> class.
	/// </summary>
	/// <param name="a_Size"> The scale/size of the triangle </param>
	/// <param name="a_Color"> The color of the triangle </param>
	Triangle(float a_Size, XMVECTOR a_Color);
	
	/// <summary>
	/// Finalizes an instance of the <see cref="Triangle"/> class and deallocates attached index/vertex buffers
	/// </summary>
	~Triangle();
	
	/// <summary>
	/// Sets the shader this triangle should be rendered with
	/// </summary>
	/// <param name="a_Shader">The shader to render the triangle wtih </param>
	void setShader(ID3DX11Effect* a_Shader);
	
	/// <summary>
	/// Sets the position of the tirangle in world space coordinates
	/// </summary>
	/// <param name="a_Position">The new position </param>
	void setPosition(CXMVECTOR a_Position);
	
	/// <summary>
	/// Draws the triangle using the specified device context
	/// </summary>
	/// <param name="a_Context">The context to draw with </param>
	/// <param name="a_ViewProjection">The view-projection matrix used by the camera</param>
	void draw(ID3D11DeviceContext* a_Context, CXMMATRIX a_ViewProjection);
	
	/// <summary>
	/// Initialises the index and vertex buffers of the triangle, since initialization needs to be delayed
	/// because of the init function in the matching assignment class
	/// </summary>
	/// <param name="a_Device">The device to use for allocating the buffers </param>
	void initialiseBuffers(ID3D11Device* a_Device);
private:	
	/// <summary>
	/// Binds the buffers of this triangle to the specified context, so they can be used for rendering
	/// </summary>
	/// <param name="a_Context">The context to bind the buffers to </param>
	void bind(ID3D11DeviceContext* a_Context) const;
};
