#pragma once
#include <stdint.h>

namespace AGPEngine
{
    struct Color
    {
    public:
        float r = 0.0f;
        float g = 0.0f;
        float b = 0.0f;
        float a = 0.0f;

        const static Color White;
        const static Color Black;
        const static Color Red;
        const static Color Blue;
        const static Color Green;
        const static Color Yellow;
        const static Color Gray;
        const static Color Magenta;
        const static Color Cyan;

    public:
        Color(float a_RedValue, float a_GreenValue, float a_BlueValue, float a_AlphaValue = 1);
        Color();
        
        static Color createFromRGBAValue(uint64_t a_Value);
    };
}