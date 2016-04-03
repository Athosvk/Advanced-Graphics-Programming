#include "Color.h"

namespace AGPEngine
{
    const Color Color::White = Color(1.0f, 1.0f, 1.0f);
    const Color Color::Black = Color(0.0f, 0.0f, 0.0f);
    const Color Color::Red = Color(1.0f, 0.0f, 0.0f);
    const Color Color::Blue = Color(0.0f, 1.0f, 0.0f);
    const Color Color::Green = Color(0.0f, 0.0f, 1.0f);
    const Color Color::Yellow = Color(0.5f, 0.5f, 0.0f);
    const Color Color::Magenta = Color(1.0f, 0.0f, 1.0f);
    const Color Color::Cyan = Color(0.0f, 1.0f, 1.0f);

    Color::Color(float a_RedValue, float a_GreenValue, float a_BlueValue, float a_AlphaValue)
    {
        r = a_RedValue;
        g = a_GreenValue;
        b = a_BlueValue;
        a = a_AlphaValue;
    }

    Color::Color()
    {
    }

    Color Color::createFromRGBAValue(uint64_t a_Value)
    {
        auto newColor = Color();

        newColor.r = (a_Value >> 24 & 0xFF) / 255.0f;
        newColor.g = (a_Value >> 16 & 0xFF) / 255.0f;
        newColor.b = (a_Value >> 8 & 0xFF) / 255.0f;
        newColor.a = (a_Value & 0xFF) / 255.0f;

        return newColor;
    }
}