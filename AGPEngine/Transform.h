#pragma once
#include <Windows.h>
#include <xnamath.h>

#include "Core/Component.h"

namespace AGPEngine
{
    class Transform : public Component
    {
    private:
        XMFLOAT3 m_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
        XMFLOAT4 m_Rotation = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
        XMFLOAT4X4 m_Matrix;
        bool m_Dirty = true;

    public:
        Transform(GameObject a_GameObject);

        XMMATRIX getMatrix();
        XMVECTOR getPosition() const;
        XMVECTOR getRotation() const;
        void setPosition(CXMVECTOR a_Position);
        void setRotation(CXMVECTOR a_Rotation);
    private:
        void refreshMatrix();
        bool isDirty() const;
    };
}
