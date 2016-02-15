#pragma once
#include <Windows.h>
#include <vector>
#include <xnamath.h>

#include "Vertex.h"

class Prism
{
public:
    static const unsigned MinimumSlices;
    static const unsigned MaximumSlices;

private:
    std::vector<Vertex> mVertices;
    std::vector<UINT> mIndices;
    float mHeight;
    unsigned mSlices;
    XMFLOAT3 mPosition;
    float mSliceRotation = 0.0f;
    float mDeltaRotation = 30.0f;
    float mTotalRotation = mSliceRotation;

public:
    Prism(unsigned aSlices, float aHeight, FXMVECTOR aPosition);

    void update(float a_DeltaTime);
    std::vector<Vertex>& getVertices();
    std::vector<UINT>& getIndices();
    unsigned getSliceCount() const;
    float getHeight() const;
    float getSliceRotation() const;
    XMVECTOR getPosition() const;
    static unsigned getMaxVertexCount();
    static unsigned getMaxIndexCount();
private:
    void Construct();
    void ConstructBase(float aYPosition, float aYNormal, CXMVECTOR aColor);
    void ConstructSides();
};