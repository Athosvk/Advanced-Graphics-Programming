#include "Prism.h"

const unsigned Prism::MinimumSlices = 3;
const unsigned Prism::MaximumSlices = 360;

Prism::Prism(unsigned aSlices, float aHeight, FXMVECTOR aPosition)
    : mHeight(aHeight),
    mSlices(aSlices)
{
    XMStoreFloat3(&mPosition, aPosition);
    if(aSlices >= MinimumSlices && aSlices <= MaximumSlices)
    {
        Construct();
    }
    else
    {
        throw std::out_of_range("Vertices exceed maximum/minimum vertices");
    }
}

std::vector<Vertex>& Prism::getVertices()
{
    return mVertices;
}

std::vector<UINT>& Prism::getIndices()
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

void Prism::Construct()
{
    ConstructBase(mHeight / 2, 1.0f, Colors::Black);
    ConstructBase(-mHeight / 2, -1.0f, Colors::White);
    ConstructSides();
}

void Prism::ConstructBase(float aYPosition, float aYNormal, CXMVECTOR aColor)
{
    const auto BaseIndex = mVertices.size();
    const auto RotationDelta = XM_2PI / mSlices;

    for(auto i = 0u; i < mSlices; i++)
    {
        float x = cosf(i * RotationDelta);
        float z = sinf(i * RotationDelta);

        mVertices.emplace_back(XMVectorSet(x, aYPosition, z, 0.0f) + XMLoadFloat3(&mPosition), aColor);
    }

    XMVECTOR center = XMVectorSet(0.0f, aYPosition, 0.0f, 0.0f) + XMLoadFloat3(&mPosition);
    mVertices.emplace_back(center, aColor);
    const auto CenterIndex = mVertices.size() - 1;

    for(auto i = 0u; i < mSlices; i++)
    {
        mIndices.push_back(CenterIndex);
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

void Prism::ConstructSides()
{
    const auto IndicesPerSlice = 3;
    const auto IndicesPerBase = mSlices * IndicesPerSlice;
    for(auto i = 0u; i < mSlices; i++)
    {
        const auto Offset = IndicesPerSlice * i;
        mIndices.push_back(mIndices[2 + IndicesPerBase + Offset]);
        mIndices.push_back(mIndices[1 + IndicesPerBase + Offset]);
        mIndices.push_back(mIndices[2 + Offset]);

        mIndices.push_back(mIndices[1 + Offset]);
        mIndices.push_back(mIndices[2 + IndicesPerBase + Offset]);
        mIndices.push_back(mIndices[2 + Offset]);
    }
}
