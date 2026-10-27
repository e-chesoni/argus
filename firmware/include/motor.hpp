#pragma once

namespace Motor
{
    enum class MotorId
    {
        frontLeft,
        frontRight,
        rearLeft,
        rearRight
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