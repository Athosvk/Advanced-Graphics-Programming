#pragma once
#include <Windows.h>
#include <xnamath.h>
#include <vector>
#include <array>

#include "../Rendering/Camera2D.h"

namespace AGPEngine
{
    enum class EMouseButton
    {
        Right = SDL_BUTTON_RIGHT,
        Left = SDL_BUTTON_LEFT,
        Middle = SDL_BUTTON_MIDDLE
    };

    class Mouse
    {
    private:
        const static int ButtonCount = 4;
        static std::array<bool, ButtonCount> s_CurrentlyPressed;
        static std::array<bool, ButtonCount> s_PreviouslyPressed;
        static XMFLOAT2 s_Position;
        static Camera2D* s_CurrentCamera;

        SDL_MouseMotionEvent m_CurrentMotion;
        std::vector<SDL_MouseButtonEvent> m_ButtonEvents;
        std::vector<SDL_MouseWheelEvent> m_ScrollEvents;

    public:
        Mouse& operator=(const Mouse& a_Other) = delete;

        void process(SDL_MouseButtonEvent a_ButtonEvent);
        void process(SDL_MouseMotionEvent a_MotionEvent);
        void process(SDL_MouseWheelEvent a_ScrollEvent);
        void update();
        void onCameraChange(Camera2D* a_NewCamera);
        static bool isButtonPressed(EMouseButton a_MouseButton);
        static bool isButtonDown(EMouseButton a_MouseButton);
        static XMVECTOR getScreenPosition();
        static XMVECTOR getWorldPosition();

    private:
        void updatePosition();
        void updateButtonStates();
    };
}
