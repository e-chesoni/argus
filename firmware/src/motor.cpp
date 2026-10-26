#include <Arduino.h>
#include <math.h>

#include "../include/motor.hpp"

// use anonymous namespace for "private" helper functions for motor class
namespace
{
    constexpr uint32_t DEFAULT_FREQ = 20000;
    constexpr uint8_t LEDC_RESOLUTION_BITS = 8;
    constexpr uint32_t LEDC_RESOLUTION = (1 << LEDC_RESOLUTION_BITS) - 1;

    struct MotorConfig
    {
        int fwdPWMPin;
        int backPWMPin;

        uint8_t fwdChannel;
        uint8_t backChannel;

        uint32_t currentFreq;
        float desiredSpeed;
    };

    MotorConfig motors[] =
    {
        {41, 40, 0, 1, DEFAULT_FREQ, 0.0f}, // Front-left
        {38, 37, 2, 3, DEFAULT_FREQ, 0.0f}, // Front-right
        {17, 16, 4, 5, DEFAULT_FREQ, 0.0f}, // Rear-left
        {8, 18, 6, 7, DEFAULT_FREQ, 0.0f}  // Rear-right
    };

    MotorConfig& getMotor(Motor::MotorId motor)
    {
        return motors[static_cast<int>(motor)];
    }

    void ledcAnalogWrite(uint8_t channel, float speed)
    {
        speed = constrain(speed, 0.0f, 1.0f);

        uint32_t duty = static_cast<uint32_t>(
            speed * LEDC_RESOLUTION
        );

        ledcWrite(channel, duty);
    }
}

// Configure motors
void Motor::setup()
{
    for (MotorConfig& motor : motors)
    {
        ledcSetup(
            motor.fwdChannel,
            motor.currentFreq,
            LEDC_RESOLUTION_BITS
        );

        ledcSetup(
            motor.backChannel,
            motor.currentFreq,
            LEDC_RESOLUTION_BITS
        );

        ledcAttachPin(motor.fwdPWMPin, motor.fwdChannel);
        ledcAttachPin(motor.backPWMPin, motor.backChannel);

        ledcWrite(motor.fwdChannel, 0);
        ledcWrite(motor.backChannel, 0);
    }
}

// Update PWM frequency
void Motor::setFreq(MotorId motor, unsigned int freq)
{
    MotorConfig& config = getMotor(motor);

    config.currentFreq = freq;

    ledcSetup(
        config.fwdChannel,
        config.currentFreq,
        LEDC_RESOLUTION_BITS
    );

    ledcSetup(
        config.backChannel,
        config.currentFreq,
        LEDC_RESOLUTION_BITS
    );
}

// Set desired motor speed
void Motor::setSpeed(MotorId motor, float speed)
{
    MotorConfig& config = getMotor(motor);

    config.desiredSpeed = constrain(speed, -1.0f, 1.0f);
}

// Apply PWM based on desired speed
void Motor::setPWM(MotorId motor)
{
    MotorConfig& config = getMotor(motor);

    if (config.desiredSpeed > 0.0f)
    {
        ledcAnalogWrite(config.backChannel, 0.0f);
        ledcAnalogWrite(config.fwdChannel, config.desiredSpeed);
    }
    else if (config.desiredSpeed < 0.0f)
    {
        ledcAnalogWrite(config.fwdChannel, 0.0f);
        ledcAnalogWrite(config.backChannel, -config.desiredSpeed);
    }
    else
    {
        stop(motor);
    }
}

// Apply the latest motor command
void Motor::updateSignal(MotorId motor)
{
    setPWM(motor);
}

// Forward at full power
void Motor::forward(MotorId motor)
{
    setSpeed(motor, 1.0f);
    updateSignal(motor);
}

// Backward at full power
void Motor::backward(MotorId motor)
{
    setSpeed(motor, -1.0f);
    updateSignal(motor);
}


// Stop motor
void Motor::stop(MotorId motor)
{
    MotorConfig& config = getMotor(motor);

    config.desiredSpeed = 0.0f;

    ledcWrite(config.fwdChannel, 0);
    ledcWrite(config.backChannel, 0);
}