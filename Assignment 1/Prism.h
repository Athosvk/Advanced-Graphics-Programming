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

public:
    Prism(unsigned aSlices, float aHeight, FXMVECTOR aPosition);

    std::vector<Vertex>& getVertices();
    std::vector<UINT>& getIndices();
    unsigned getSliceCount() const;
    float getHeight() const;
    XMVECTOR getPosition() const;
    static unsigned getMaxVertexCount();
    static unsigned getMaxIndexCount();
private:
    void Construct();
    void ConstructBase(float aYPosition, float aYNormal);
    void ConstructSides();
};