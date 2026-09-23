#pragma once

namespace Joystick
{
    constexpr int xCenter = 1964;
    constexpr int yCenter = 1952;
    constexpr int deadzone = 100;

    void setup();

    int getX();
    int getY();

    bool isXCentered(int x);
    bool isYCentered(int y);
}