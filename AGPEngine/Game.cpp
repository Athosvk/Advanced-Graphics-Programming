#define NOMINMAX
#include <Windows.h>

#include "MathHelper.h"
#include "Game.h"

namespace AGPEngine
{
    const double Game::FixedUpdateInterval = 0.015;
    const double Game::SpiralOfDeathThreshold = 0.075;

    Game::Game(int a_ScreenWidth, int a_ScreenHeight, std::wstring a_WindowName, HINSTANCE a_ApplicationHandle)
        : m_Window(a_ScreenWidth, a_ScreenHeight, a_WindowName, a_ApplicationHandle)
    {
        loadWorld<World>();
    }

    int Game::run()
    {
        return startGameLoop();
    }

    int Game::startGameLoop()
    {
        while(m_CurrentGameState == GameState::Play)
        {
            m_Window.clear();
            processEvents();
            update();
            processFixedUpdates();
            m_Window.renderCurrentFrame();
        }
        return 0;
    }

    void Game::update()
    {
        m_CurrentWorld->update();
        m_GameTime.update();
    }

    void Game::processFixedUpdates()
    {
        m_FixedUpdateTimer += m_GameTime.getDeltaTime();

        m_FixedUpdateTimer = MathHelper::min(SpiralOfDeathThreshold, m_FixedUpdateTimer);
        while(m_FixedUpdateTimer >= FixedUpdateInterval)
        {
            m_FixedUpdateTimer -= FixedUpdateInterval;
            fixedUpdate();
        }
    }

    void Game::fixedUpdate()
    {
        m_CurrentWorld->fixedUpdate();
    }

    void Game::processEvents()
    {
        std::vector<Event> unhandledEvents;
        while(!m_EventQueue.isEmpty())
        {
            auto windowEvent = m_EventQueue.dequeue();
            switch(windowEvent.EventType)
            {
            case WM_QUIT:
                m_CurrentGameState = GameState::Exit;
                break;
            default:
                unhandledEvents.push_back(windowEvent);
            }
        }
        m_CurrentWorld->processEvents(unhandledEvents);
    }
}

