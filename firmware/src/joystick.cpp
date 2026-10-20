#include <Arduino.h>

#include "../include/joystick.hpp"

namespace
{
    constexpr int xPin = 5;
    constexpr int yPin = 6;
    
    float normalize(int value, int center)
    {
        int offset = value - center;

        if (abs(offset) <= Joystick::deadzone)
            return 0.0f;

        if (offset > 0)
        {
            return static_cast<float>(
                offset - Joystick::deadzone
            ) / (4095 - center - Joystick::deadzone);
        }

        return static_cast<float>(
            offset + Joystick::deadzone
        ) / (center - Joystick::deadzone);
    }
}

void Joystick::setup()
{
    pinMode(xPin, INPUT);
    pinMode(yPin, INPUT);
}

int Joystick::getX()
{
    return analogRead(xPin);
}

int Joystick::getY()
{
    return analogRead(yPin);
}

float Joystick::getNormalizedX()
{
    return normalize(getX(), xCenter);
}

float Joystick::getNormalizedY()
{
    return normalize(getY(), yCenter);
}

bool Joystick::isXCentered(int x)
{
    return x >= xCenter - deadzone &&
           x <= xCenter + deadzone;
}

bool Joystick::isYCentered(int y)
{
    return y >= yCenter - deadzone &&
           y <= yCenter + deadzone;
}