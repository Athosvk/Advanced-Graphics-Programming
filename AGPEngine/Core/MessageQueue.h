#pragma once
#include <vector>
#include <memory>
#include <typeindex>

#include "MessagingSystem.h"

namespace AGPEngine
{
    class MessageQueue
    {
    private:
        struct QueuedMessage
        {
        private:
            std::unique_ptr<Message> m_Message;
            std::type_index m_MessageType;
            GameObject m_Target;

        public:
            QueuedMessage(std::unique_ptr<Message>&& a_Message, std::type_index a_Type, GameObject a_Target);

            const Message* getMessage() const;
            std::type_index getMessageType() const;
            GameObject getTarget() const;
        };

        std::vector<QueuedMessage> m_Messages;

    public:
        auto begin()->decltype(m_Messages.begin());
        auto end()->decltype(m_Messages.end());
        void clear();
        bool isEmpty() const;

        template<typename TMessageType, typename ...TArguments>
        void enqueue(GameObject a_Target, TArguments&&... a_MessageArguments)
        {
            auto message = std::make_unique<TMessageType>(std::forward<TArguments>(a_MessageArguments)...);
            m_Messages.emplace_back(std::move(message), typeid(TMessageType), a_Target);
        }
    };
}
