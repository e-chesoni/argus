#include <Arduino.h>

#include "../include/onboardLed.hpp"
#include "../include/externalLed.hpp"
#include "../include/joystick.hpp"
#include "../include/motor.hpp"

constexpr int externalLedPin = 2;

void setup()
{
    // Start serial comms
    Serial.begin(115200);
    delay(2000);

    Serial.println("Argus testing joystick");
    
    // Init relevant hardware
    OnboardLed::setup();
    //ExternalLed::setup();
    Joystick::setup();
    Motor::setup();

    // Set the onboard LED to purple once at startup
    Serial.println("Setting onboard LED to purple");
    OnboardLed::setColor(OnboardLed::purple);
}

void loop()
{
    // Continuously read the joystick position
    int x = Joystick::getX();
    int y = Joystick::getY();

    // Print the current joystick position
    Serial.print("X: ");
    Serial.print(x);

    Serial.print("\tY: ");
    Serial.println(y);

    if (Joystick::isYCentered(y))
    {
        Motor::stop(Motor::MotorId::frontLeft);
        Motor::stop(Motor::MotorId::frontRight);
        Motor::stop(Motor::MotorId::rearLeft);
        Motor::stop(Motor::MotorId::rearRight);
    }
    else if (y > Joystick::yCenter)
    {
        Motor::forward(Motor::MotorId::frontLeft);
        Motor::forward(Motor::MotorId::frontRight);
        Motor::forward(Motor::MotorId::rearLeft);
        Motor::forward(Motor::MotorId::rearRight);
    }
    else
    {
        Motor::backward(Motor::MotorId::frontLeft);
        Motor::backward(Motor::MotorId::frontRight);
        Motor::backward(Motor::MotorId::rearLeft);
        Motor::backward(Motor::MotorId::rearRight);
    }

    // Slow output to make serial monitor is readable
    delay(50);
}