#pragma once
#include "GameTime.h"
#include "Core/World.h"
#include "EventQueue.h"
#include "Window.h"

namespace AGPEngine
{
    enum class GameState
    {
        Play, Exit
    };

    class Game
    {
    public:
        static const double FixedUpdateInterval;

    protected:
        static const double SpiralOfDeathThreshold;

        GameState m_CurrentGameState = GameState::Play;
        GameTime m_GameTime;
        std::unique_ptr<World> m_CurrentWorld;
        EventQueue m_EventQueue;
        Window m_Window;
    private:
        double m_FixedUpdateTimer = 0.0;

    public:
        Game(int a_ScreenWidth, int a_ScreenHeight, std::wstring a_WindowName, HINSTANCE a_ApplicationHandle);
    public:
        virtual ~Game() = default;

        int run();

    protected:
        void update();
        void fixedUpdate();

        template<typename T>
        void loadWorld()
        {
            m_CurrentWorld = std::make_unique<T>(m_GameTime);
        }

    private:
        int startGameLoop();
        void processFixedUpdates();
        void processEvents();
    };
}