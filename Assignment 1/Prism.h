#pragma once
#include <Windows.h>
#include <vector>
#include <xnamath.h>
#include <Vertex.h>

/// <summary>
/// An n-prism used for rendering purposes
/// </summary>
class Prism
{
public:
	/// <summary>
	/// The minimum amount of slices a prism can have
	/// </summary>
	/// <remarks> 
	/// Slices is also known as the vertices on the base of the prism.
	/// The constructor will throw if you go below this limit, so use this 
	/// to restrict the slices used for construction of the prism
	/// </remarks>
    static const unsigned MinimumSlices;
	/// <summary>
	/// The maximum amount of slices a prism can have
	/// </summary>
	/// <remarks> 
	/// Slices is also known as the vertices on the base of the prism.
	/// The constructor will throw if you exceed this limit, so use this 
	/// to limit the slices used for construction of the prism
	/// </remarks>
    static const unsigned MaximumSlices;
	/// <summary>
	/// The factor by which vertical slices should rotate in degrees per second
	/// </summary>
	static const float DeltaRotation;

private:
	/// <summary>
	/// The vertices used to render the prism
	/// </summary>
	std::vector<Vertex> mVertices;
	/// <summary>
	/// The indices used to render the prism
	/// </summary>
	std::vector<UINT> mIndices;
	/// <summary>
	/// The prism's height
	/// </summary>
	float mHeight;
	/// <summary>
	/// The amount of slices of the prism
	/// </summary>
	/// <remarks> Also known as the amount of vertices on the base of the prism </remarks>
	unsigned mSlices;
	/// <summary>
	/// The position of the prism in world space coordinates
	/// </summary>
	XMFLOAT3 mPosition;
	/// <summary>
	/// The factor with which the vertical slices should be rotated in degrees
	/// </summary>
	float mSliceRotation = 0.0f;	
	/// <summary>
	/// The total rotation, non-interpolated between the minimum and maximum rotation,
	/// so we can derive the interpolated rotation
	/// </summary>
	float mTotalRotation = mSliceRotation;

public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="Prism"/> class.
	/// </summary>
	/// <param name="aSlices"> The amount of slices of the prism </param>
	/// <param name="aHeight"> The height of the to be created prism </param>
	/// <param name="aPosition"> The position in world space coordinates </param>
	Prism(unsigned aSlices, float aHeight, FXMVECTOR aPosition);
	
	/// <summary>
	/// Updates the (rotation of) the prism
	/// </summary>
	/// <param name="a_DeltaTime">The the time passed since the last update</param>
	void update(float a_DeltaTime);	

	/// <summary>
	/// Gets the vertices created for this prism
	/// </summary>
	/// <returns> The vector containing all the vertices of the prism </returns>
	const std::vector<Vertex>& getVertices() const;	

	/// <summary>
	/// Gets the indices created for this prism
	/// </summary>
	/// <returns> The vector containinig all the indices of the prism </returns>
	const std::vector<UINT>& getIndices() const;

	/// <summary>
	/// Gets the amount of slices this prism has
	/// </summary>
	/// <returns> The slice count </returns>
	unsigned getSliceCount() const;

	/// <summary>
	/// Gets the height of the prism
	/// </summary>
	/// <returns> The height of the prism</returns>
	float getHeight() const;
	
	/// <summary>
	/// Gets the current rotation of the vertical slices
	/// </summary>
	/// <returns> The rotation of the vertical slices </returns>
	/// <remarks> Used to set the matching variable in the fx file </remarks>
	float getSliceRotation() const;
	
	/// <summary>
	/// Gets the position of the prism in world space coordinates
	/// </summary>
	/// <returns> The position in world space coordinates </returns>
	XMVECTOR getPosition() const;
		
	/// <summary>
	/// Gets the maximum amount of vertices a prism will use, based on the maximum 
	/// amount of slices it can have
	/// </summary>
	/// <returns> The maximum amount of vertices a prism will use</returns>
	/// <remarks> Used to pre-allocate appropriately sized vertex buffers for the prism </remarks>
	static unsigned getMaxVertexCount();
	
	/// <summary>
	/// Gets the maximum amount of indices a prism will use, based on the maximum
	/// amount of slices it can have
	/// </summary>
	/// <returns> The maximum amount of indices a prism will use </returns>
	/// <remarks> Used to pre-allocate appropriately sized index buffers for the prism </remarks>
	static unsigned getMaxIndexCount();
private:	
	/// <summary>
	/// Constructs the prism
	/// </summary>
	void construct();
	
	/// <summary>
	/// Constructs a base of the prism
	/// </summary>
	/// <param name="aYPosition"> The Y position of the base </param>
	/// <param name="aYNormal"> The Y normal of the base, to determine the correct winding order </param>
	/// <param name="aColor"> Color of the vertices of the base </param>
	void constructBase(float aYPosition, float aYNormal, CXMVECTOR aColor);
	
	/// <summary>
	/// Constructs the sides/horizontal slices of the prism, based on the existing 
	/// vectors of indices and vertices
	/// </summary>
	void constructSides();
};