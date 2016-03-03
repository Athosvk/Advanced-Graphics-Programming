#pragma once
#include <vector>

namespace AGPEngine
{
    class GameTime
    {
    private:
        double m_CurrentTime = 0.0;
        double m_PreviousTime = 0.0;;
        double m_DeltaTime = 0.0;
        int m_CurrentFrame = 1;
        int m_SampleCount = 15;
        std::vector<double> m_Samples;

    public:
        GameTime();

        double getCurrentTime() const;
        double getDeltaTime() const;
        double getAverageDeltaTime() const;
        void setFrameSampleCount(int a_FrameSampleCount);
        void update();
    private:
        double queryTime() const;
    };
}

