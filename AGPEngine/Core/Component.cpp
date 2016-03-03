#include "Component.h"

namespace AGPEngine
{
    Component::Component(GameObject a_GameObject)
        : m_GameObject(a_GameObject)
    {
    }

    GameObject Component::getGameObject()
    {
        return m_GameObject;
    }
}