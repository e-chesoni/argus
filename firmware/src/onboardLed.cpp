#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#include "../include/onboardLed.hpp"

namespace
{
    constexpr int rgbLedPin = 48;
    constexpr int numPixels = 1;
    constexpr int brightness = 30;

    Adafruit_NeoPixel pixel(
        numPixels,
        rgbLedPin,
        NEO_GRB + NEO_KHZ800
    );
}

void OnboardLed::setup()
{
    pixel.begin();
    pixel.setBrightness(brightness);
    pixel.clear();
    pixel.show();
}

void OnboardLed::setColor(uint32_t color)
{
    pixel.setPixelColor(0, color);
    pixel.show();
}

void OnboardLed::clear()
{
    pixel.clear();
    pixel.show();
}