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

public:
    Prism(unsigned aBaseVertices);

    const std::vector<Vertex>& getVertices() const;
    const std::vector<UINT>& getIndices() const;

private:
    void Construct(unsigned aBaseVertices);
    void ConstructBase(unsigned aBaseVertices, float aYPosition);
    void ConstructSides(unsigned aBaseVertices);
};