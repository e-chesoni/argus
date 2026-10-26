#include <Arduino.h>
#include <math.h>

#include "../include/drive.hpp"
#include "../include/motor.hpp"

using Id = Motor::MotorId;

void Drive::setup()
{
    Motor::setup();
}

// TODO: test both move and specific motion cmds (then delete one--you don't need both)

void Drive::move(float x, float y)
{
    float frontLeft  = y + x;
    float frontRight = y - x;
    float rearLeft   = y - x;
    float rearRight  = y + x;

    // Normalize so no wheel exceeds 100% command
    float maxSpeed = max(1.0f, max(abs(frontLeft),
                     max(abs(frontRight),
                     max(abs(rearLeft), abs(rearRight)))));

    frontLeft  /= maxSpeed;
    frontRight /= maxSpeed;
    rearLeft   /= maxSpeed;
    rearRight  /= maxSpeed;

    // Set desired motor speeds
    Motor::setSpeed(Id::frontLeft, frontLeft);
    Motor::setSpeed(Id::frontRight, frontRight);
    Motor::setSpeed(Id::rearLeft, rearLeft);
    Motor::setSpeed(Id::rearRight, rearRight);

    // Apply PWM signals to motors
    Motor::updateSignal(Id::frontLeft);
    Motor::updateSignal(Id::frontRight);
    Motor::updateSignal(Id::rearLeft);
    Motor::updateSignal(Id::rearRight);
}