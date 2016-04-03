#pragma once
namespace AGPEngine
{
    class MathHelper
    {
    public:
        MathHelper() = delete;
        ~MathHelper() = delete;

        static float clamp(float a_Value, float a_Min, float a_Max);
        static float pingPong(float a_Value, float a_Min, float a_Max);

        template<typename T>
        static T min(T a_Value1, T a_Value2)
        {
            return a_Value1 < a_Value2 ? a_Value1 : a_Value2;
        }

        template<typename T>
        static T max(T a_Value1, T a_Value2)
        {
            return a_Value1 > a_Value2 ? a_Value1 : a_Value2;
        }
    };
}
