#pragma once
#include <LightHelper.h>
#include <memory>
#include <Model.h>

/// <summary>
/// Represents a simple combination of a mesh/model and a material
/// </summary>
class MeshRenderer
{
public:
    std::unique_ptr<Model> MeshData;
    Material MeshMaterial;
};
