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

    Motor::setSpeed(Id::frontLeft, frontLeft);
    Motor::setSpeed(Id::frontRight, frontRight);
    Motor::setSpeed(Id::rearLeft, rearLeft);
    Motor::setSpeed(Id::rearRight, rearRight);
}

void Drive::forward()
{
    Motor::forward(Id::frontLeft);
    Motor::forward(Id::frontRight);
    Motor::forward(Id::rearLeft);
    Motor::forward(Id::rearRight);
}

void Drive::backward()
{
    Motor::backward(Id::frontLeft);
    Motor::backward(Id::frontRight);
    Motor::backward(Id::rearLeft);
    Motor::backward(Id::rearRight);
}

void Drive::strafeLeft()
{
    Motor::backward(Id::frontLeft);
    Motor::forward(Id::frontRight);
    Motor::forward(Id::rearLeft);
    Motor::backward(Id::rearRight);
}

void Drive::strafeRight()
{
    Motor::forward(Id::frontLeft);
    Motor::backward(Id::frontRight);
    Motor::backward(Id::rearLeft);
    Motor::forward(Id::rearRight);
}

void Drive::rotateLeft()
{
    Motor::backward(Id::frontLeft);
    Motor::forward(Id::frontRight);
    Motor::backward(Id::rearLeft);
    Motor::forward(Id::rearRight);
}

void Drive::rotateRight()
{
    Motor::forward(Id::frontLeft);
    Motor::backward(Id::frontRight);
    Motor::forward(Id::rearLeft);
    Motor::backward(Id::rearRight);
}

void Drive::diagonalFrontLeft()
{
    Motor::stop(Id::frontLeft);
    Motor::forward(Id::frontRight);
    Motor::forward(Id::rearLeft);
    Motor::stop(Id::rearRight);
}

void Drive::diagonalFrontRight()
{
    Motor::forward(Id::frontLeft);
    Motor::stop(Id::frontRight);
    Motor::stop(Id::rearLeft);
    Motor::forward(Id::rearRight);
}

void Drive::diagonalBackLeft()
{
    Motor::backward(Id::frontLeft);
    Motor::stop(Id::frontRight);
    Motor::stop(Id::rearLeft);
    Motor::backward(Id::rearRight);
}

void Drive::diagonalBackRight()
{
    Motor::stop(Id::frontLeft);
    Motor::backward(Id::frontRight);
    Motor::backward(Id::rearLeft);
    Motor::stop(Id::rearRight);
}

void Drive::stop()
{
    Motor::stop(Id::frontLeft);
    Motor::stop(Id::frontRight);
    Motor::stop(Id::rearLeft);
    Motor::stop(Id::rearRight);
}