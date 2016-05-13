#pragma once
#include <d3dUtil.h>

/// <summary>
/// Represents a simple quad that can be rendered to
/// </summary>
class Quad
{
private:	
	/// <summary>
	/// The shader to use for the rendering of the quad
	/// </summary>
	ID3DX11Effect* m_Shader = nullptr;	
	/// <summary>
	/// The world transform matrix of the quad
	/// </summary>
	XMFLOAT4X4 m_Transform;	
	/// <summary>
	/// The handle to the index buffer of this quad, so it can be bound for rendering
	/// </summary>
	ID3D11Buffer* m_IndexBuffer = nullptr;
	/// <summary>
	/// The handle to the vertex buffer of this quad, so it can be bound for rendering
	/// </summary>
    ID3D11Buffer* m_VertexBuffer = nullptr;	
	/// <summary>
	/// The handle to the MVP/Transform matrix variable of the shader stored in m_Shader
	/// </summary>
	ID3DX11EffectMatrixVariable* m_ShaderMVP;	
	/// <summary>
	/// The handle to the time variable of the shader stored in m_Shader
	/// </summary>
	ID3DX11EffectScalarVariable* m_ShaderTime;	
	/// <summary>
	/// The time passed since the quad was created
	/// </summary>
	/// <remarks> Stored to be used as variable for the shader </remarks>
	float m_TimePassed = 0.0f;

public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="Quad"/> class.
	/// </summary>
	Quad();	
	/// <summary>
	/// Finalizes an instance of the <see cref="Quad"/> class as well as deallocate GPU resoruces attached
	/// </summary>
	~Quad();
	
	/// <summary>
	/// Sets the shader to be used for rendering the quad
	/// </summary>
	/// <param name="a_Shader">The shader to use </param>
	void setShader(ID3DX11Effect* a_Shader);
	
	/// <summary>
	/// Sets the position of the quad in world space coordinates
	/// </summary>
	/// <param name="a_Position">The new position </param>
	void setPosition(CXMVECTOR a_Position);
	
	/// <summary>
	/// Updates the quad ('s time passed)
	/// </summary>
	/// <param name="a_DeltaTime">The time since the last update </param>
	void update(float a_DeltaTime);
	
	/// <summary>
	/// Draws the quad using the specified DeviceContext
	/// </summary>
	/// <param name="a_Context">The DeviceContext to draw with </param>
	/// <param name="a_ViewProjection">The view-projection matrix of the camera </param>
	void draw(ID3D11DeviceContext* a_Context, CXMMATRIX a_ViewProjection);	

	/// <summary>
	/// Initialises the buffers on the given ID3D11Device
	/// </summary>
	/// <param name="a_Device">The ID3D11Devie to allocate the buffers on</param>
	void initialiseBuffers(ID3D11Device* a_Device);
private:	
	/// <summary>
	/// Binds the buffers to the specified context to use for rendering
	/// </summary>
	/// <param name="a_Context">The ID3D11DeviceContext to bind to </param>
	void bind(ID3D11DeviceContext* a_Context) const;
};

