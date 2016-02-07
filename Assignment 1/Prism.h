#pragma once
#include <Windows.h>
#include <vector>
#include <xnamath.h>

#include "Vertex.h"

class Prism
{
private:
    std::vector<Vertex> mVertices;
    std::vector<UINT> mIndices;
    float mHeight;
    unsigned mSlices;

public:
    Prism(unsigned aSlices, float aHeight);

    const std::vector<Vertex>& getVertices() const;
    const std::vector<UINT>& getIndices() const;
    unsigned getSliceCount() const;
private:
    void Construct();
    void ConstructBase(float aYPosition, float aYNormal);
    void ConstructSides();
};