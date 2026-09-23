#pragma once

#include <cstdint>

namespace OnboardLed
{
    // Standard colors
    constexpr uint32_t off    = 0x000000;
    constexpr uint32_t red    = 0xFF0000;
    constexpr uint32_t green  = 0x00FF00;
    constexpr uint32_t blue   = 0x0000FF;
    constexpr uint32_t purple = 0xFF00FF;
    constexpr uint32_t white  = 0xFFFFFF;

    void setup();
    void setColor(uint32_t color);
    void clear();
}