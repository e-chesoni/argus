#include <Arduino.h>

#include "../include/motor.hpp"

namespace
{
    struct MotorPins
    {
        int in1;
        int in2;
    };

    constexpr MotorPins frontLeftPins  = {41, 40};
    constexpr MotorPins frontRightPins = {39, 38};
    constexpr MotorPins rearLeftPins   = {16, 15};
    constexpr MotorPins rearRightPins  = {18, 17};

    MotorPins getPins(Motor::MotorId motor)
    {
        switch (motor)
        {
            case Motor::MotorId::frontLeft:
                return frontLeftPins;

            case Motor::MotorId::frontRight:
                return frontRightPins;

            case Motor::MotorId::rearLeft:
                return rearLeftPins;

            case Motor::MotorId::rearRight:
                return rearRightPins;
        }

        return { -1, -1 };
    }
}

void Motor::setup()
{
    // Configure the front-left motor control pins as outputs
    pinMode(frontLeftPins.in1, OUTPUT);
    pinMode(frontLeftPins.in2, OUTPUT);
    pinMode(frontRightPins.in1, OUTPUT);
    pinMode(frontRightPins.in2, OUTPUT);
    pinMode(rearLeftPins.in1, OUTPUT);
    pinMode(rearLeftPins.in2, OUTPUT);
    pinMode(rearRightPins.in1, OUTPUT);
    pinMode(rearRightPins.in2, OUTPUT);

    // Start with the motor stopped
    digitalWrite(frontLeftPins.in1, LOW);
    digitalWrite(frontLeftPins.in2, LOW);
    digitalWrite(frontRightPins.in1, LOW);
    digitalWrite(frontRightPins.in2, LOW);
    digitalWrite(rearLeftPins.in1, LOW);
    digitalWrite(rearLeftPins.in2, LOW);
    digitalWrite(rearRightPins.in1, LOW);
    digitalWrite(rearRightPins.in2, LOW);
}

void Motor::forward(MotorId motor)
{
    MotorPins pins = getPins(motor);

    digitalWrite(pins.in1, HIGH);
    digitalWrite(pins.in2, LOW);
}

void Motor::backward(MotorId motor)
{
    MotorPins pins = getPins(motor);

    digitalWrite(pins.in1, LOW);
    digitalWrite(pins.in2, HIGH);
}

void Motor::stop(MotorId motor)
{
    MotorPins pins = getPins(motor);

    digitalWrite(pins.in1, LOW);
    digitalWrite(pins.in2, LOW);
}