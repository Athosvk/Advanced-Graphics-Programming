#include "MessageQueue.h"

namespace AGPEngine
{
    MessageQueue::QueuedMessage::QueuedMessage(std::unique_ptr<BadEngine::Message>&& a_Message, 
        std::type_index a_Type, GameObject a_Target)
        : m_Message(std::move(a_Message)),
        m_MessageType(a_Type),
        m_Target(a_Target)
    {
    }

    const Message* MessageQueue::QueuedMessage::getMessage() const
    {
        return m_Message.get();
    }

    std::type_index MessageQueue::QueuedMessage::getMessageType() const
    {
        return m_MessageType;
    }

    GameObject MessageQueue::QueuedMessage::getTarget() const
    {
        return m_Target;
    }

    auto MessageQueue::begin()->decltype(m_Messages.begin())
    {
        return m_Messages.begin();
    }

    auto MessageQueue::end()->decltype(m_Messages.end())
    {
        return m_Messages.end();
    }

    void MessageQueue::clear()
    {
        m_Messages.clear();
    }

    bool MessageQueue::isEmpty() const
    {
        return m_Messages.empty();
    }
}
