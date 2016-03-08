#pragma once
#if defined(WIN32) || defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#else 
#include <chrono>
#endif

namespace AGPEngine
{
    class StopWatch
    {
    private:
        bool m_Finished;

#if defined(WIN32) || defined(_WIN32) || defined(_WIN64)
        LARGE_INTEGER m_StartTime;
        LARGE_INTEGER m_EndTime;
#else
        std::chrono::high_resolution_clock::time_point m_StartTime;
        std::chrono::high_resolution_clock::time_point m_EndTime;
#endif

    public:
        StopWatch();

        static StopWatch startNew();
        void start();
        void end();

    public:
        long long toNanoseconds();

    private:
#if defined(WIN32) || defined(_WIN32) || defined(_WIN64)
        LARGE_INTEGER getCurrentTime();
#else
        std::chrono::system_clock::time_point getCurrentTime();
#endif
    };
};
