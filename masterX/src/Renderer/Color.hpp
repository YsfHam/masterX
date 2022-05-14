#pragma once

#include <cstdint>

namespace mx
{
    struct Color
    {
        float r, g, b, a;

        static const Color Black;
        static const Color White;
        static const Color Red  ;
        static const Color Green;
        static const Color Blue ;
    };

    struct RGBA8Color
    {
        uint8_t r, g, b, a;

        RGBA8Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
            : r(red), g(green), b(blue), a(alpha)
        {}

        operator Color()
        {
            const float max = (float)(uint8_t)(~0);
            Color res;
            res.r = r / max;
            res.g = g / max;
            res.b = b / max;
            res.a = a / max;

            return res;
        }
    };
}