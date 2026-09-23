#include <Arduino.h>

#include "../include/externalLed.hpp"

namespace
{
    constexpr int ledPin = 2;
}

void ExternalLed::setup()
{
    pinMode(ledPin, OUTPUT);
    off();
}

void ExternalLed::on()
{
    digitalWrite(ledPin, HIGH);
}

void ExternalLed::off()
{
    digitalWrite(ledPin, LOW);
}