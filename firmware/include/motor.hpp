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

    // Motor configuration
    void setFreq(MotorId motor, unsigned int freq);
    void setSpeed(MotorId motor, float speed);

    // Apply motor commands
    void setPWM(MotorId motor);
    void updateSignal(MotorId motor);

    // Existing motor commands
    void forward(MotorId motor);
    void backward(MotorId motor);
    void stop(MotorId motor);
}