#pragma once
#include <vector>

#include "MessagingSystem.h"

namespace AGPEngine
{
    class EntitySystem;

    class System
    {
    protected:
        EntitySystem& m_EntitySystem;
        MessagingSystem& m_MessagingSystem;

    public:
        System(EntitySystem& a_EntitySystem, MessagingSystem& a_MessagingSystem);

        virtual void registerListeners() = 0;
    };
}