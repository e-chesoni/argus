#include <Arduino.h>

#include "../include/joystick.hpp"

namespace
{
    constexpr int xPin = 5;
    constexpr int yPin = 6;
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