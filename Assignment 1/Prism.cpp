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
    ConstructBase(aSlices, mHeight / 2, 1.0f);
    ConstructBase(aSlices, -mHeight / 2, -1.0f);
    ConstructSides(aSlices);
}

void Prism::ConstructBase(unsigned aSlices, float aYPosition, float aYNormal)
{
    const auto BaseIndex = mVertices.size();
    const auto RotationDelta = XM_2PI / aSlices;

    for(auto i = 0u; i < aSlices; i++)
    {
        float x = cosf(i * RotationDelta);
        float z = sinf(i * RotationDelta);

        mVertices.emplace_back(XMFLOAT3(x, aYPosition, z));
    }

    mVertices.emplace_back(XMFLOAT3(0.0f, aYPosition, 0.0f));
    const auto CenterIndex = mVertices.size() - 1;

    for(auto i = 0u; i < aSlices; i++)
    {
        mIndices.push_back(CenterIndex);
        if(aYNormal < 0.0f)
        {
            mIndices.push_back(BaseIndex + i);
            mIndices.push_back((i + 1) % aSlices + BaseIndex);
        }
        else
        {
            mIndices.push_back((i + 1) % aSlices + BaseIndex);
            mIndices.push_back(BaseIndex + i);
        }
    }
}

void Prism::ConstructSides(unsigned aSlices)
{
    const auto IndicesPerBase = aSlices * 3;
    const auto IndicesPerSlice = 3;
    for(auto i = 0u; i < aSlices; i++)
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
