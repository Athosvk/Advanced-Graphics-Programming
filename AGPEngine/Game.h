#pragma once
#include "GameTime.h"
#include "Core/World.h"
#include "EventQueue.h"

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
        const float m_OpenGLVersion = 3.00f;
        static const double SpiralOfDeathThreshold;

        GameState m_CurrentGameState = GameState::Play;
        GameTime m_GameTime;
        std::unique_ptr<World> m_CurrentWorld;
        EventQueue m_EventQueue;
        
    private:
        double m_FixedUpdateTimer = 0.0;

    protected:
        Game(int a_ScreenWidth, int a_ScreenHeight, std::string a_WindowName);
    public:
        virtual ~Game() = default;

        void run();

    protected:
        void update();
        void fixedUpdate();

        template<typename T>
        void loadWorld()
        {
            m_CurrentWorld = std::make_unique<T>(m_GameTime);
        }

    private:
        void startGameLoop();
        void processFixedUpdates();
        void processEvents();
    };
}