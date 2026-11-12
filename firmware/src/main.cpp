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
    Joystick::setup();

    Drive::setup();
    Encoder::setup();

    // Set the onboard LED to purple once at startup
    Serial.println("Setting onboard LED to purple");
    OnboardLed::setColor(OnboardLed::purple);

    Serial.begin(115200);
    delay(2000);
    analogReadResolution(12);
}

void loop()
{
    int rawX = Joystick::getX();;
    int rawY = Joystick::getY();;

    float x = Joystick::getNormalizedX();
    float y = Joystick::getNormalizedY();

    // Read encoders
    // Serial.print("FL: ");
    // Serial.print(Encoder::getCount(Motor::MotorId::frontLeft));

    // Serial.print("\tFR: ");
    // Serial.print(Encoder::getCount(Motor::MotorId::frontRight));

    // Serial.print("\tRL: ");
    // Serial.print(Encoder::getCount(Motor::MotorId::rearLeft));

    // Serial.print("\tRR: ");
    // Serial.println(Encoder::getCount(Motor::MotorId::rearRight));
    

    Drive::move(x, y);

    // Serial.printf(
    //     "GPIO4: %d, normalized x: %.2f | GPIO5: %d, normalized y: %.2f\n",
    //     rawX, x, rawY, y
    // );


    delay(50); // 200 or 50
}