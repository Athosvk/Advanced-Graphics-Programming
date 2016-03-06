#include "Keyboard.h"

namespace AGPEngine
{
    const int Keyboard::KeyCount = 512;
    bool Keyboard::m_CurrentlyPressed[KeyCount];
    bool Keyboard::m_PreviouslyPressed[KeyCount];

    Keyboard::Keyboard()
    {
        clear();
    }

    Keyboard::~Keyboard()
    {
    }

    void Keyboard::process(KeyboardEvent a_KeyEvent)
    {
        if(a_KeyEvent.Key < KeyCount)
        {
            m_KeyboardEvents.push_back(a_KeyEvent);
        }
    }

    bool Keyboard::isDown(const KeyCode& a_KeyCode)
    {
        return m_CurrentlyPressed[static_cast<int>(a_KeyCode)];
    }

    bool Keyboard::isPressed(const KeyCode& a_KeyCode)
    {
        return isDown(a_KeyCode) && !m_PreviouslyPressed[static_cast<int>(a_KeyCode)];
    }

    bool Keyboard::isReleased(const KeyCode& a_KeyCode)
    {
        return !isDown(a_KeyCode) && m_PreviouslyPressed[static_cast<int>(a_KeyCode)];
    }

    void Keyboard::clear()
    {
        clearPrevious();
        clearCurrent();
    }

    void Keyboard::clearPrevious()
    {
        for(auto i = 0; i < KeyCount; ++i)
        {
            m_PreviouslyPressed[i] = false;
        }
    }

    void Keyboard::clearCurrent()
    {
        for(auto i = 0; i < KeyCount; ++i)
        {
            m_CurrentlyPressed[i] = false;
        }
    }

    void Keyboard::updateKeystate()
    {
        for(auto i = 0; i < KeyCount; ++i)
        {
            m_PreviouslyPressed[i] = m_CurrentlyPressed[i];
        }

        for(auto& keyEvent : m_KeyboardEvents)
        {
            m_CurrentlyPressed[keyEvent.Key] = keyEvent.Pressed;
        }
        m_KeyboardEvents.clear();
    }

    void Keyboard::update()
    {
        updateKeystate();
    }
};