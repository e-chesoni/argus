#include <Arduino.h>

#include "../include/onboardLed.hpp"
#include "../include/externalLed.hpp"
#include "../include/joystick.hpp"
#include "../include/motor.hpp"
#include "../include/drive.hpp"
#include "../include/encoder.hpp"

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
    //Motor::setup();
    Drive::setup();
    Encoder::setup();

    // Set the onboard LED to purple once at startup
    Serial.println("Setting onboard LED to purple");
    OnboardLed::setColor(OnboardLed::purple);
}

void loop()
{
    float x = Joystick::getNormalizedX();
    float y = Joystick::getNormalizedY();

    // Read encoders
    Serial.print("FL: ");
    Serial.print(Encoder::getCount(Motor::MotorId::frontLeft));

    Serial.print("\tFR: ");
    Serial.print(Encoder::getCount(Motor::MotorId::frontRight));

    Serial.print("\tRL: ");
    Serial.print(Encoder::getCount(Motor::MotorId::rearLeft));

    Serial.print("\tRR: ");
    Serial.println(Encoder::getCount(Motor::MotorId::rearRight));

    // If this works, you dont need specific strafe, diagonal, etc. cmds in drive files
    Drive::move(x, y);

    Serial.print("X: ");
    Serial.print(x);

    Serial.print("\tY: ");
    Serial.println(y);

    delay(50);
}