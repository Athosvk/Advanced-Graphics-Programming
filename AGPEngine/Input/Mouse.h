#pragma once
#include <Windows.h>
#include <xnamath.h>
#include <vector>
#include <array>

namespace AGPEngine
{
    enum class EMouseButton
    {
        Right = 0,
        Left = 1,
        Middle = 2
    };

    class MouseButtonEvent
    {
    public:
        EMouseButton Button;
        bool Pressed;
    };

    class MouseMotionEvent
    {
    public:
        int X = 0; 
        int Y = 0;
    };

    class Mouse
    {
    private:
        const static int ButtonCount = 3;
        static std::array<bool, ButtonCount> s_CurrentlyPressed;
        static std::array<bool, ButtonCount> s_PreviouslyPressed;
        static XMFLOAT2 s_Position;

        MouseMotionEvent m_CurrentMotion;
        std::vector<MouseButtonEvent> m_ButtonEvents;

    public:
        Mouse& operator=(const Mouse& a_Other) = delete;

        void process(MouseButtonEvent a_ButtonEvent);
        void process(MouseMotionEvent a_MotionEvent);
        void update();
        static bool isButtonPressed(EMouseButton a_MouseButton);
        static bool isButtonDown(EMouseButton a_MouseButton);
        static XMVECTOR getScreenPosition();

    private:
        void updatePosition();
        void updateButtonStates();
    };
}
