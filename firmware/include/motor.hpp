#pragma once

namespace Motor
{
    // NOTE: order here must match MotorConfig in motor.cpp
    enum class MotorId
    {
        rearRight = 0,
        frontRight = 1,
        frontLeft = 2,
        rearLeft = 3
    };

    void setup();

    // configure motor
    void setFreq(MotorId motor, unsigned int freq);
    void setSpeed(MotorId motor, float speed);

    // use to apply motor commands
    void setPWM(MotorId motor);
    void updateSignal(MotorId motor);

    // basic motor commands
    void forward(MotorId motor);
    void backward(MotorId motor);
    void stop(MotorId motor);
}