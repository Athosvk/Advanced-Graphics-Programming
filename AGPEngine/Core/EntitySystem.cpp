#include "EntitySystem.h"
#include "GameObject.h"

namespace AGPEngine
{   
    EntityActivatedMessage::EntityActivatedMessage(GameObject a_Entity)
        : m_ActivatedEntity(a_Entity)
    {
    }

    GameObject EntityActivatedMessage::getActivatedEntity() const
    {
        return m_ActivatedEntity;
    }

    EntityDeactivatedMessage::EntityDeactivatedMessage(GameObject a_Entity)
        : m_DeactivatedEntity(a_Entity)
    {
    }

    GameObject EntityDeactivatedMessage::getDeactivatedEntity() const
    {
        return m_DeactivatedEntity;
    }

    EntitySystem::EntitySystem(MessagingSystem& a_MessagingSystem)
        : m_MessagingSystem(a_MessagingSystem)
    {
    }

    bool EntitySystem::isActive(GameObject a_Entity)
    {
        return m_EntityStates[a_Entity.getID()].Active;
    }

    void EntitySystem::activate(GameObject a_Entity)
    {
        m_EntityStates[a_Entity.getID()].Active = true;
        m_MessagingSystem.sendMessage<EntityActivatedMessage>(a_Entity, a_Entity);
    }

    void EntitySystem::deactivate(GameObject a_Entity)
    {
        m_EntityStates[a_Entity.getID()].Active = false;
        m_MessagingSystem.sendMessage<EntityDeactivatedMessage>(a_Entity, a_Entity);
    }

    unsigned EntitySystem::generateNextID()
    {
        return m_LastID++;
    }
}