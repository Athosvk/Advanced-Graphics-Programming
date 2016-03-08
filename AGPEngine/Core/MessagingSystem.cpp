#include "MessagingSystem.h"
#include "MessageQueue.h"

namespace AGPEngine
{
    void MessagingSystem::dispatchQueue(MessageQueue& a_MessageQueue)
    {
        for(const auto& message : a_MessageQueue)
        {
            sendMessage(message.getTarget(), message.getMessage(), message.getMessageType());
        }
    }

    void MessagingSystem::sendMessage(GameObject a_Target, const Message* a_Message,
        std::type_index a_Type)
    {
        auto typeIterator = m_ObjectMessageListeners.find(a_Type);

        if(typeIterator != m_ObjectMessageListeners.end())
        {
            auto listenerIterator = typeIterator->second.find(a_Target.getID());
            if(listenerIterator != typeIterator->second.end())
            {
                listenerIterator->second(a_Message);
            }
        }
    }
}
