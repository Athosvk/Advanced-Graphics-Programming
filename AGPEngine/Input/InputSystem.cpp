#include <Windowsx.h>

#include "InputSystem.h"
#include "../Core/World.h"

namespace AGPEngine
{
    InputSystem::InputSystem(EntitySystem& a_EntitySystem, MessagingSystem& a_MessagingSystem)
        : System(a_EntitySystem, a_MessagingSystem)
    {
    }

    void InputSystem::registerListeners()
    {
        m_MessagingSystem.registerListener<ProcessEventsMessage>([this](const AGPEngine::Message* a_Message)
        {
            processEvents(static_cast<const ProcessEventsMessage*>(a_Message)->getEvents());
            updateInput();
        });
    }

    void InputSystem::processEvents(const std::vector<Event>& a_Events)
    {
        for(auto windowEvent : a_Events)
        {
            switch(windowEvent.EventType)
            {
            case WM_KEYDOWN:
            case WM_KEYUP:
            {
                KeyboardEvent keyboardEvent{ windowEvent.EventType == WM_KEYDOWN,
                    windowEvent.Parameter1 };
                m_Keyboard.process(keyboardEvent);
                break;
            }
            case WM_LBUTTONDOWN:
            case WM_LBUTTONUP:
            {
                MouseButtonEvent buttonEvent{ EMouseButton::Left, windowEvent.EventType == WM_LBUTTONDOWN };
                m_Mouse.process(buttonEvent);
                break;
            }
            case WM_RBUTTONDOWN:
            case WM_RBUTTONUP:
            {
                MouseButtonEvent buttonEvent{ EMouseButton::Right, windowEvent.EventType == WM_RBUTTONDOWN };
                m_Mouse.process(buttonEvent);
                break;
            }
            case WM_MBUTTONDOWN:
            case WM_MBUTTONUP:
            {
                MouseButtonEvent buttonEvent{ EMouseButton::Middle, windowEvent.EventType == WM_MBUTTONDOWN };
                m_Mouse.process(buttonEvent);
            }
            case WM_MOUSEMOVE:
            {
                MouseMotionEvent motionEvent;
                motionEvent.X = static_cast<int>(GET_X_LPARAM(windowEvent.Parameter2));
                motionEvent.Y = static_cast<int>(GET_Y_LPARAM(windowEvent.Parameter2));
                m_Mouse.process(motionEvent);
                break;
            }
            }
        }
    }

    void InputSystem::updateInput()
    {
        m_Mouse.update();
        m_Keyboard.update();
        m_MessagingSystem.broadcast<HandleInputMessage>();
    }
}
