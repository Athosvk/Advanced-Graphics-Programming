#pragma once
#include <Windows.h>
#include <vector>

#include "Keycode.h"

namespace AGPEngine
{
    class KeyboardEvent
    {
    public:
        bool Pressed;
        WPARAM Key;
    };

    class Keyboard
    {
    private:
        std::vector<KeyboardEvent> m_KeyboardEvents;
        
        static const int KeyCount;
        static bool m_PreviouslyPressed[512];
        static bool m_CurrentlyPressed[512];

    public:
        Keyboard();
        ~Keyboard();

        void process(KeyboardEvent a_KeyEvent);
        void update();

        static bool isPressed(const KeyCode& a_KeyCode);
        static bool isDown(const KeyCode& a_KeyCode);
        static bool isReleased(const KeyCode& a_KeyCode);
        static void clear();

    private:
        static void clearPrevious();
        static void clearCurrent();
        void updateKeystate();
    };
}