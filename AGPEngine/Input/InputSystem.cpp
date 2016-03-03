#include "InputSystem.h"
#include "../Core/World.h"
#include "../Rendering/Camera2D.h"

namespace AGPEngine
{
    InputSystem::InputSystem(EntitySystem& a_EntitySystem, MessagingSystem& a_MessagingSystem)
        : System(a_EntitySystem, a_MessagingSystem)
    {
        auto cameras = m_EntitySystem.getComponentsOfType<Camera2D>();
        if(!cameras.empty())
        {
            m_Mouse.onCameraChange(cameras[0]);
        }
    }

    void InputSystem::registerListeners()
    {
        m_MessagingSystem.registerListener<OnCameraChangedMessage>([this](const BadEngine::Message* a_Message)
        {
            m_Mouse.onCameraChange(static_cast<const OnCameraChangedMessage*>(a_Message)->getNewCamera());
        });
        m_MessagingSystem.registerListener<ProcessEventsMessage>([this](const BadEngine::Message* a_Message)
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
                m_Keyboard.process(windowEvent.Parameter1);
                break;
            case WM_LBUTTONDOWN:
            case WM_LBUTTONUP:
            case WM_RBUTTONDOWN:
            case WM_RBUTTONUP:
                m_Mouse.process(windowEvent.button);
                break;
            case WM_MOUSEMOVE:
                m_Mouse.process(windowEvent.motion);
                break;
            case WM_MOUSEWHEEL:
                m_Mouse.process(windowEvent.wheel);
                break;
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
