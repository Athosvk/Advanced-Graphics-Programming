#include <Windows.h>

#include "GameTime.h"

namespace AGPEngine
{
    GameTime::GameTime()
        : m_Samples(m_SampleCount)
    {
    }

    void GameTime::setFrameSampleCount(int a_FrameSampleCount)
    {
        m_SampleCount = a_FrameSampleCount;
        m_Samples.resize(a_FrameSampleCount);
    }

    double GameTime::getCurrentTime() const
    {
        return m_CurrentTime;
    }

    double GameTime::getDeltaTime() const
    {
        return m_DeltaTime;
    }

    double GameTime::getAverageDeltaTime() const
    {
        auto average = 0.0;
        for(auto i = 0; i < m_SampleCount; ++i)
        {
            average += m_Samples[i];
        }
        average /= m_SampleCount;
        return average;
    }

    void GameTime::update()
    {
        m_DeltaTime = m_CurrentTime - m_PreviousTime;
        m_PreviousTime = m_CurrentTime;
        m_CurrentTime = queryTime();
        m_Samples[++m_CurrentFrame % m_SampleCount] = m_DeltaTime;
    }

    double GameTime::queryTime() const
    {
        LARGE_INTEGER currentTime;
        QueryPerformanceCounter(&currentTime);

        LARGE_INTEGER frequency;
        QueryPerformanceFrequency(&frequency);
        return (currentTime.QuadPart * 1000) / static_cast<double>(frequency.QuadPart);
    }
}