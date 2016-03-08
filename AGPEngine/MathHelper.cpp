#include <math.h>

#include "MathHelper.h"

namespace AGPEngine
{
    float MathHelper::clamp(float a_Value, float a_Min, float a_Max)
    {
        if(a_Value <= a_Min)
        {
            return a_Min;
        }
        if(a_Value >= a_Max)
        {
            return a_Max;
        }
        return a_Value;
    }

    float MathHelper::pingPong(float a_Value, float a_Min, float a_Max)
    {
        auto length = a_Max - a_Min;
        auto wrappedValue = fmod(a_Value, length * 2);
        if(wrappedValue > length)
        {
            wrappedValue = 2 * length - wrappedValue;
        }
        return wrappedValue;
    }
}
