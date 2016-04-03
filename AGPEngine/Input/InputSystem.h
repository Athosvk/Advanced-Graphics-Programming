#pragma once
#include "../Core/System.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "../EventQueue.h"

namespace AGPEngine
{
    class HandleInputMessage : public Message
    {

    };

    class InputSystem : public System
    {
    private:
        Keyboard m_Keyboard;
        Mouse m_Mouse;

    public:
        InputSystem(EntitySystem& a_EntitySystem, MessagingSystem& a_MessagingSystem);

        virtual void registerListeners() override;
    private:
        void processEvents(const std::vector<Event>& a_Events);
        void updateInput();
    };
}