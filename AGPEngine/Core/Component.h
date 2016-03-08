#pragma once
#include "GameObject.h"

namespace AGPEngine
{
    class Component
    {
        GameObject m_GameObject;

    protected:
        Component(GameObject a_GameObject);
        ~Component() = default;

    public:
        template<typename T>
        T* getComponent() const
        {
            return m_GameObject.getComponent<T>();
        }

        template<typename T>
        T* addComponent()
        {
            return m_GameObject.addComponent<T>();
        }

        GameObject getGameObject();
    };
}
