#include "Keyboard.h"

namespace AGPEngine
{
    bool Keyboard::m_CurrentlyPressed[SDL_NUM_SCANCODES];
    bool Keyboard::m_PreviouslyPressed[SDL_NUM_SCANCODES];

    Keyboard::Keyboard()
    {
        clear();
    }

    Keyboard::~Keyboard()
    {
    }

    void Keyboard::process(WPARAM a_KeyEvent)
    {
        m_KeyboardEvents.push_back(a_KeyEvent);
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
        for(auto i = 0; i < SDL_NUM_SCANCODES; ++i)
        {
            m_PreviouslyPressed[i] = false;
        }
    }

    void Keyboard::clearCurrent()
    {
        for(auto i = 0; i < SDL_NUM_SCANCODES; ++i)
        {
            m_CurrentlyPressed[i] = false;
        }
    }

    void Keyboard::updateKeystate()
    {
        for(auto i = 0; i < SDL_NUM_SCANCODES; ++i)
        {
            m_PreviouslyPressed[i] = m_CurrentlyPressed[i];
        }

        for(auto& keyEvent : m_KeyboardEvents)
        {
            m_CurrentlyPressed[keyEvent] = iterator->type != SDL_KEYUP;
        }
        m_KeyboardEvents.clear();
    }

    void Keyboard::update()
    {
        updateKeystate();
    }
};