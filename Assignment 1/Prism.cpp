#include "Prism.h"

Prism::Prism(unsigned aSlices, float aHeight)
    : mHeight(aHeight)
{
    const unsigned MinimalVertices = 3;
    if(aSlices >= MinimalVertices)
    {
        Construct(aSlices);
    }
    else
    {
        throw std::out_of_range("Less vertices than possible");
    }
}

const std::vector<Vertex>& Prism::getVertices() const
{
    return mVertices;
}

const std::vector<UINT>& Prism::getIndices() const
{
    return mIndices;
}

void Prism::Construct(unsigned aSlices)
{
    ConstructBase(aSlices, mHeight / 2);
    ConstructBase(aSlices, -mHeight / 2);
    ConstructSides(aSlices);
}

void Prism::ConstructBase(unsigned aSlices, float aYPosition)
{
    const auto BaseIndex = mVertices.size();
    const auto RotationDelta = XM_2PI / aSlices;

    for(auto i = 0u; i < aSlices; i++)
    {
        float x = cosf(i * RotationDelta) * 0.5f;
        float z = sinf(i * RotationDelta) * 0.5f;

        mVertices.emplace_back(XMFLOAT3(x, aYPosition, z));
    }

    mVertices.emplace_back(XMFLOAT3(0.0f, aYPosition, 0.0f));
    const auto CenterIndex = mVertices.size() - 1;

    for(auto i = 0u; i < aSlices; i++)
    {
        mIndices.push_back(CenterIndex);
        mIndices.push_back(BaseIndex + i);
        mIndices.push_back((i + 1) % aSlices + BaseIndex);
    }
}

void Prism::ConstructSides(unsigned aSlices)
{
    const auto IndicesPerBase = aSlices * 3;
    const auto IndicesPerSlice = 3;
    for(auto i = 0u; i < aSlices; i++)
    {
        mIndices.push_back(mIndices[i * IndicesPerSlice + 1]);
        mIndices.push_back(mIndices[i * IndicesPerSlice + 1 + IndicesPerBase]);
        mIndices.push_back(mIndices[i * IndicesPerSlice + 2]);
        mIndices.push_back(mIndices[i * IndicesPerSlice + 1 + IndicesPerBase]);
        mIndices.push_back(mIndices[i * IndicesPerSlice + 2 + IndicesPerBase]);
        mIndices.push_back(mIndices[i * IndicesPerSlice + 2]);
    }
}
