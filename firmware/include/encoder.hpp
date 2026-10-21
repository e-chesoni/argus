#pragma once

#include "motor.hpp"

namespace Encoder
{
    void setup();

    long getCount(Motor::MotorId motor);
    void reset(Motor::MotorId motor);
}