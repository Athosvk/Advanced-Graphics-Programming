#pragma once
#include <memory>
#include <unordered_map>
#include <map>
#include <functional>
#include <typeindex>

#include "../Delegate.h"
#include "GameObject.h"

namespace AGPEngine
{
    class MessageQueue;

    class Message
    {
    };

    class MessagingSystem
    {
    private:
        std::unordered_map<std::type_index, Delegate<void(const Message*)>> m_MessageListeners;
        std::unordered_map<std::type_index, std::map<unsigned, Delegate<void(const Message*)>>> m_ObjectMessageListeners;

    public:
        template<typename TMessageType, typename... TArguments>
        void broadcast(TArguments&&... a_MessageArguments)
        {
            auto newMessage = TMessageType(std::forward<TArguments>(a_MessageArguments)...);

            auto iterator = m_MessageListeners.find(typeid(TMessageType));
            if(iterator != m_MessageListeners.end())
            {
                iterator->second(&newMessage);
            }
        }

        template<typename TMessageType, typename... TArguments>
        void sendMessage(GameObject a_GameObject, TArguments&&... a_MessageArguments)
        {
            auto newMessage = TMessageType(std::forward<TArguments>(a_MessageArguments)...);
            sendMessage(a_GameObject, &newMessage, typeid(TMessageType));
        }

        void dispatchQueue(MessageQueue& a_MessageQueue);

        template<typename TMessageType>
        void registerListener(std::function<void(const Message* a_Message)> a_Callback)
        {
            m_MessageListeners[typeid(TMessageType)] += a_Callback;
        }

        template<typename TMessageType>
        void registerListener(std::function<void(const Message* a_Message)> a_Callback, GameObject a_GameObject)
        {
            m_ObjectMessageListeners[typeid(TMessageType)][a_GameObject.getID()] += a_Callback;
        }

    private:
        void sendMessage(GameObject a_Target, const Message* a_Message, std::type_index a_Type);
    };
}
