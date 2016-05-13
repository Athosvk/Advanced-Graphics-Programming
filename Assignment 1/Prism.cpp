#include "Prism.h"

const unsigned Prism::MinimumSlices = 3;
const unsigned Prism::MaximumSlices = 360;
const float Prism::DeltaRotation = 30.0f;

Prism::Prism(unsigned aSlices, float aHeight, FXMVECTOR aPosition)
    : mHeight(aHeight),
    mSlices(aSlices)
{
    XMStoreFloat3(&mPosition, aPosition);
    if(aSlices >= MinimumSlices && aSlices <= MaximumSlices)
    {
        construct();
    }
    else
    {
        throw std::out_of_range("Vertices exceed maximum/minimum vertices");
    }
}

void Prism::update(float a_DeltaTime)
{
    mSliceRotation = XMConvertToRadians(MathHelper::PingPong(mTotalRotation, 0.0f, 90.0f));
    mTotalRotation += DeltaRotation * a_DeltaTime;
}

const std::vector<Vertex>& Prism::getVertices() const
{
    return mVertices;
}

const std::vector<UINT>& Prism::getIndices() const
{
    return mIndices;
}

unsigned Prism::getSliceCount() const
{
    return mSlices;
}

float Prism::getHeight() const
{
    return mHeight;
}

float Prism::getSliceRotation() const
{
    return mSliceRotation;
}

XMVECTOR Prism::getPosition() const
{
    return XMLoadFloat3(&mPosition);
}

unsigned Prism::getMaxIndexCount()
{
    return MaximumSlices * 12;
}

unsigned Prism::getMaxVertexCount()
{
    return MaximumSlices * 2 + 2;
}

void Prism::construct()
{
    constructBase(mHeight / 2, 1.0f, Colors::Black);
    constructBase(-mHeight / 2, -1.0f, Colors::Green);
    constructSides();
}

void Prism::constructBase(float aYPosition, float aYNormal, CXMVECTOR aColor)
{
    const auto BaseIndex = mVertices.size();
    const auto RotationDelta = XM_2PI / mSlices;

    for(auto i = 0u; i < mSlices; i++)
    {
        float x = cos(i * RotationDelta);
        float z = sin(i * RotationDelta);

        float RBColor = i * (1.0f / mSlices);
        mVertices.emplace_back(XMVectorSet(x, aYPosition, z, 0.0f) + XMLoadFloat3(&mPosition), 
            aColor + XMVectorSet(RBColor, 0.0f, RBColor, 0.0f));
    }

    XMVECTOR center = XMVectorSet(0.0f, aYPosition, 0.0f, 0.0f) + XMLoadFloat3(&mPosition);
    mVertices.emplace_back(center, aColor);
    const auto CenterIndex = mVertices.size() - 1;

    for(auto i = 0u; i < mSlices; i++)
    {
        mIndices.push_back(CenterIndex);
		//Correct the winding order of the indices based on the normal of the base
        if(aYNormal < 0.0f)
        {
            mIndices.push_back(BaseIndex + i);
            mIndices.push_back((i + 1) % mSlices + BaseIndex);
        }
        else
        {
            mIndices.push_back((i + 1) % mSlices + BaseIndex);
            mIndices.push_back(BaseIndex + i);
        }
    }
}

void Prism::constructSides()
{
    const auto IndicesPerSlice = 3;
    const auto IndicesPerBase = mSlices * IndicesPerSlice;
    for(auto i = 0u; i < mSlices; i++)
    {
        const auto Offset = IndicesPerSlice * i;
		//Gather the indices from the base and re-use them for the sides
		/*
			Quad layout, based on order of push backs:

			1/5 ---- 2
			|      / |
			|     /  |
			|    /	 |
			|   /	 |
			|  /	 |
			| /		 |
			|/		 |
			4 ------ 3/6
		*/
        mIndices.push_back(mIndices[2 + IndicesPerBase + Offset]);
        mIndices.push_back(mIndices[1 + IndicesPerBase + Offset]);
        mIndices.push_back(mIndices[2 + Offset]);

        mIndices.push_back(mIndices[1 + Offset]);
        mIndices.push_back(mIndices[2 + IndicesPerBase + Offset]);
        mIndices.push_back(mIndices[2 + Offset]);
    }
}
