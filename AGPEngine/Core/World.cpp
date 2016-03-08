#include "World.h"
#include "../Input/InputSystem.h"

namespace AGPEngine
{
    UpdateMessage::UpdateMessage(const GameTime& a_GameTime)
        : m_GameTime(a_GameTime)
    {
    }

    const GameTime& UpdateMessage::getGameTime() const
    {
        return m_GameTime;
    }

    ProcessEventsMessage::ProcessEventsMessage(const std::vector<Event>& a_Events)
        : m_Events(a_Events)
    {
    }

    const std::vector<Event>& ProcessEventsMessage::getEvents() const
    {
        return m_Events;
    }

    World::World(GameTime& a_GameTime)
        : m_EntitySystem(m_MessagingSystem),
        m_GameTime(a_GameTime)
    {
        addDefaultSystems();
    }

    void World::addDefaultSystems()
    {
        auto mainCamera = m_EntitySystem.createEntity();

        addSystem<InputSystem>();
    }

    void World::update()
    {
        broadcast<UpdateMessage>(m_GameTime);
        broadcast<RenderMessage>();
        m_GameTime.update();
    }

    void World::fixedUpdate()
    {
        broadcast<FixedUpdateMessage>();
    }

    void World::processEvents(std::vector<Event>& a_Events)
    {
        broadcast<ProcessEventsMessage>(a_Events);
    }
}