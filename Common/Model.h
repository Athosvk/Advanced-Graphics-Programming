#pragma once
#include <assimp/vector2.h>
#include <assimp/vector3.h>
#include <assimp/color4.h>
#include <vector>
#include <d3d11.h>

#include "Vertex.h"

/// <summary>
/// Represents a mesh that can be loaded from disk
/// </summary>
/// <remarks> 
/// Not to be used for meshes that contain submeshes, does not load materials
/// Supports the same file formats as supported by the Open Asset Import Library (assimp)
/// </remarks>
class Model
{
private:	
	/// <summary>
	/// The mirrored CPU list of vertices to be used for the mesh
	/// </summary>
	std::vector<Vertex> m_Vertices;	
	/// <summary>
	/// The mirrored CPU list of the indices to be used for the mesh
	/// </summary>
	std::vector<UINT> m_Indices;	
	/// <summary>
	/// The handle to the vertex buffer resource, so we can bind it at run-time for rendering
	/// </summary>
	ID3D11Buffer* m_VertexBuffer;	
	/// <summary>
	/// The handle to the index buffer resource, so we can bind it at run-time for rendering
	/// </summary>
	ID3D11Buffer* m_IndexBuffer;

public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="Model"/> class.
	/// </summary>
	/// <param name="a_Filepath">The path to the model </param>
	/// <param name="a_Device">The D3D11 device to allocate the buffers on </param>
	Model(const std::string& a_Filepath, ID3D11Device* a_Device);

	/// <summary>
	/// Finalizes an instance of the <see cref="Model"/> class and de-allocates vertex and index buffers
	/// </summary>
	~Model();
	
	/// <summary>
	/// Draws the model using the specified device context
	/// </summary>
	/// <param name="a_Contex">The device context</param>
	void draw(ID3D11DeviceContext* a_Context);
	
	/// <summary>
	/// Binds the buffers of this model to the specified context, so that the buffers can be bound to it
	/// </summary>
	/// <param name="a_Context">The context to bind to </param>
	void bind(ID3D11DeviceContext* a_Context);
private:	
	/// <summary>
	/// Converts a given assimp vector to those used by the xnamath library
	/// </summary>
	/// <param name="a_Vector">The vector to convert </param>
	/// <returns>The converted-to 2D vector </returns>
	XMFLOAT2 toXMFloat2(aiVector3D a_Vector);
	
	/// <summary>
	/// Converts a given assimp vector to those used by the xnamath library
	/// </summary>
	/// <param name="a_Vector">The vector to convert </param>
	/// <returns> The converted-to 3D vector</returns>
	XMFLOAT3 toXMFloat3(aiVector3D a_Vector);
	
	/// <summary>
	/// Converts a given assimp color to those used by the xnamath library
	/// </summary>
	/// <param name="a_Color"> The color vector to convert </param>
	/// <returns> The converted-to 4D vector, representing a color </returns>
	XMFLOAT4 toXMFloat4(aiColor4D a_Color);
	
	/// <summary>
	/// Retrieves the mesh data at the given filepath, so it can be used for storing on the GPU
	/// </summary>
	/// <param name="a_Filepath">The path to the mesh </param>
	void loadMeshdata(const std::string& a_Filepath);
	
	/// <summary>
	/// Builds the index buffer from the mesh data
	/// </summary>
	/// <param name="a_Device">The Direct3D device to build the index buffer for </param>
	void buildIndexBuffer(ID3D11Device* a_Device);
	
	/// <summary>
	/// Builds the index buffer from the mesh data
	/// </summary>
	/// <param name="a_Device">The Direct3D device to build the vertex buffer for </param>
	void buildVertexBuffer(ID3D11Device* a_Device);
};
