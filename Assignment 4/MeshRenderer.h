#pragma once
#include <LightHelper.h>
#include <memory>

class Mesh;

class MeshRenderer
{
public:
    std::unique_ptr<Mesh> MeshData;
    Material MeshMaterial;
};
