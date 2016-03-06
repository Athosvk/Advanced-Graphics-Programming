#include "Mouse.h"

namespace AGPEngine
{
    std::array<bool, Mouse::ButtonCount> Mouse::s_CurrentlyPressed;
    std::array<bool, Mouse::ButtonCount> Mouse::s_PreviouslyPressed;
    XMFLOAT2 Mouse::s_Position;

    void Mouse::process(MouseButtonEvent a_ButtonEvent)
    {
        m_ButtonEvents.push_back(a_ButtonEvent);
    }

    void Mouse::process(MouseMotionEvent a_MotionEvent)
    {
        m_CurrentMotion = a_MotionEvent;
    }

    void Mouse::update()
    {
        updatePosition();
        updateButtonStates();
    }

    bool Mouse::isButtonPressed(EMouseButton a_MouseButton)
    {
        return isButtonDown(a_MouseButton) && !s_PreviouslyPressed[static_cast<int>(a_MouseButton)];
    }

    bool Mouse::isButtonDown(EMouseButton a_MouseButton)
    {
        return s_CurrentlyPressed[static_cast<int>(a_MouseButton)];
    }

    XMVECTOR Mouse::getScreenPosition()
    {
        return XMLoadFloat2(&s_Position);
    }

    void Mouse::updatePosition()
    {
        s_Position.x = static_cast<float>(m_CurrentMotion.X);
        s_Position.y = static_cast<float>(m_CurrentMotion.Y);
    }

    void Mouse::updateButtonStates()
    {
        for(auto i = 0; i < ButtonCount; ++i)
        {
            s_PreviouslyPressed[i] = s_CurrentlyPressed[i];
        }

        for(auto& buttonEvent : m_ButtonEvents)
        {
            s_CurrentlyPressed[static_cast<int>(buttonEvent.Button)] = buttonEvent.Pressed;
        }
        m_ButtonEvents.clear();
    }
}