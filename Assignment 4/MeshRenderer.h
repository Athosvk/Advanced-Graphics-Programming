#pragma once
#include <LightHelper.h>
#include <memory>
#include <Model.h>

class MeshRenderer
{
public:
    std::unique_ptr<Model> MeshData;
    Material MeshMaterial;
};
