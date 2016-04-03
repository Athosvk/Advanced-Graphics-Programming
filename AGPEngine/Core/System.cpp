#include "System.h"
#include "EntitySystem.h"

namespace AGPEngine
{
    System::System(EntitySystem& a_EntitySystem, MessagingSystem& a_MessagingSystem)
        : m_EntitySystem(a_EntitySystem),
        m_MessagingSystem(a_MessagingSystem)
    {
    }
}