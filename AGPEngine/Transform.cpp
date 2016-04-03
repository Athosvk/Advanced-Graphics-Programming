#include "Transform.h"

namespace AGPEngine
{
    Transform::Transform(GameObject a_GameObject)
        : Component(a_GameObject)
    {
    }

    XMMATRIX Transform::getMatrix()
    {
        if(m_Dirty)
        {
            refreshMatrix();
        }
        return XMLoadFloat4x4(&m_Matrix);
    }

    XMVECTOR Transform::getPosition() const
    {
        return XMLoadFloat3(&m_Position);
    }

    XMVECTOR Transform::getRotation() const
    {
        return XMLoadFloat4(&m_Rotation);
    }

    void Transform::setPosition(CXMVECTOR a_Position)
    {
        XMStoreFloat3(&m_Position, a_Position);
        m_Dirty = true;
    }

    void Transform::setRotation(CXMVECTOR a_Rotation)
    {
        XMStoreFloat4(&m_Rotation, a_Rotation);
        m_Dirty = true;
    }

    void Transform::refreshMatrix()
    {
        XMStoreFloat4x4(&m_Matrix, XMMatrixAffineTransformation(XMVectorZero(), XMLoadFloat3(&m_Position), 
            XMLoadFloat4(&m_Rotation), XMLoadFloat3(&m_Position)));
        m_Dirty = false;
    }
}