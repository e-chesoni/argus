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

    void forward(MotorId motor);
    void backward(MotorId motor);
    void stop(MotorId motor);
}