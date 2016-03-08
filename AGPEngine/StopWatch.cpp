#include "StopWatch.h"

namespace AGPEngine
{
#if !(defined(WIN32) || defined(_WIN32) || defined(_WIN64))
    using namespace std::chrono;
#endif

    StopWatch::StopWatch()
    {
    }

    StopWatch StopWatch::startNew()
    {
        StopWatch stopWatch;
        stopWatch.start();
        return stopWatch;
    }

    void StopWatch::start()
    {
        m_Finished = false;
        m_StartTime = getCurrentTime();
    }

    void StopWatch::end()
    {
        m_EndTime = getCurrentTime();
        m_Finished = true;
    }

#if defined(WIN32) || defined(_WIN32) || defined(_WIN64)
    long long StopWatch::toNanoseconds()
    {
        auto timePassed = (m_Finished ? m_EndTime.QuadPart : getCurrentTime().QuadPart) - m_StartTime.QuadPart;
        LARGE_INTEGER frequency;
        QueryPerformanceFrequency(&frequency);
        return (timePassed * 1000) / frequency.QuadPart;
    }
    
    LARGE_INTEGER StopWatch::getCurrentTime()
    {
        LARGE_INTEGER currentTime;
        QueryPerformanceCounter(&currentTime);
        return currentTime;
    }
#else
    long long StopWatch::toNanoseconds()
    {
        auto timePassed = (m_Finished ? m_EndTime : getCurrentTime()) - m_StartTime;
        return duration_cast<nanoseconds>(timePassed).count();
    }
    
    system_clock::time_point StopWatch::getCurrentTime()
    {
        return high_resolution_clock::now();
    }
#endif

};
