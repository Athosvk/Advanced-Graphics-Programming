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

public:
    Prism(unsigned aSlices, float aHeight);

    std::vector<Vertex>& getVertices();
    std::vector<UINT>& getIndices();
    unsigned getSliceCount() const;
    float getHeight() const;
    static unsigned getMaxVertexCount();
    static unsigned getMaxIndexCount();
private:
    void Construct();
    void ConstructBase(float aYPosition, float aYNormal);
    void ConstructSides();
};