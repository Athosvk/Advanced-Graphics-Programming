#pragma once
#include <Windows.h>
#include <xnamath.h>
#include <d3dUtil.h>

/// <summary>
/// The vertex structure used as input for the Vertex shader
/// </summary>
struct Vertex
{	
	/// <summary>
	/// The (relative) position of this vertex on the mesh
	/// </summary>
	XMFLOAT3 Position;	

	/// <summary>
	/// The color of the vertex
	/// </summary>
	/// <remarks> Interpolates between the other vertices in the triangle on the GPU </remarks>
	XMFLOAT4 Color;
	
	/// <summary>
	/// The normal of this vertex
	/// </summary>
	XMFLOAT3 Normal;
	
	/// <summary>
	/// The uv coordinates of this vertex, to be used for mapping textures
	/// </summary>
	XMFLOAT2 UVCoordinates = XMFLOAT2(0.0f, 0.0f);
	
	/// <summary>
	/// Initializes a new instance of the <see cref="Vertex"/> struct.
	/// </summary>
	Vertex() = default;
	
	/// <summary>
	/// Initializes a new instance of the <see cref="Vertex"/> struct.
	/// </summary>
	/// <param name="a_Position">The (relative) position of this vertex </param>
	/// <param name="a_Color">The color of this vertex</param>
	/// <param name="a_Normal">The normal of the vertex</param>
	/// <param name="a_UVCoordinates">The uv coordinates of the vertex</param>
	Vertex(FXMVECTOR a_Position, FXMVECTOR a_Color = Colors::White, FXMVECTOR a_Normal = XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f),
        CXMVECTOR a_UVCoordinates = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f))
    {
        XMStoreFloat3(&Position, a_Position);
        XMStoreFloat4(&Color, a_Color);
        XMStoreFloat3(&Normal, a_Normal);
        XMStoreFloat2(&UVCoordinates, a_UVCoordinates);
    }

	/// <summary>
	/// Initializes a new instance of the <see cref="Vertex"/> struct.
	/// </summary>
	/// <param name="a_Position">The position of the vertex </param>
	/// <param name="a_Color"> The color of the vertex </param>
	/// <param name="a_Normal">The normal of the vertex </param>
	/// <param name="a_UVCoordinates">The uv coordinates of the vertex</param>
	Vertex(XMFLOAT3 a_Position, XMFLOAT4 a_Color = reinterpret_cast<const float*>(&Colors::White),
        XMFLOAT3 a_Normal = XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT2 a_UVCoordinates = XMFLOAT2(0.0f, 0.0f))
        : Position(a_Position), Color(a_Color), Normal(a_Normal),
        UVCoordinates(a_UVCoordinates)
    {
    }
};