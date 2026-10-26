
#include <Arduino.h>

#include "../include/encoder.hpp"

namespace
{
    struct EncoderPins
    {
        int pinA;
        int pinB;
    };

    struct EncoderState
    {
        volatile long count = 0;
        uint8_t previousState = 0;
    };

    // TODO: Replace with your actual encoder GPIO pins.
    // These are EXAMPLE assignments only.
    constexpr EncoderPins frontLeftPins  = {15, 6};
    constexpr EncoderPins frontRightPins = {10, 9};
    constexpr EncoderPins rearLeftPins   = {12, 11};
    constexpr EncoderPins rearRightPins  = {14, 13};

    EncoderState frontLeftState;
    EncoderState frontRightState;
    EncoderState rearLeftState;
    EncoderState rearRightState;

    // Protect shared encoder state between ISR and main loop.
    portMUX_TYPE encoderMux = portMUX_INITIALIZER_UNLOCKED;

    EncoderState* getState(Motor::MotorId motor)
    {
        switch (motor)
        {
            case Motor::MotorId::frontLeft:
                return &frontLeftState;

            case Motor::MotorId::frontRight:
                return &frontRightState;

            case Motor::MotorId::rearLeft:
                return &rearLeftState;

            case Motor::MotorId::rearRight:
                return &rearRightState;
        }

        return nullptr;
    }

    void ARDUINO_ISR_ATTR handleTransition(
        EncoderState* state,
        const EncoderPins& pins)
    {
        uint8_t a = digitalRead(pins.pinA);
        uint8_t b = digitalRead(pins.pinB);

        uint8_t currentState = (a << 1) | b;

        portENTER_CRITICAL_ISR(&encoderMux);

        uint8_t transition =
            (state->previousState << 2) | currentState;

        switch (transition)
        {
            // Positive rotation
            case 0b0010:
            case 0b1011:
            case 0b1101:
            case 0b0100:
                state->count++;
                break;

            // Negative rotation
            case 0b0001:
            case 0b0111:
            case 0b1110:
            case 0b1000:
                state->count--;
                break;

            default:
                break;
        }

        state->previousState = currentState;

        portEXIT_CRITICAL_ISR(&encoderMux);
    }

    // Each interrupt callback identifies its own encoder.
    void ARDUINO_ISR_ATTR frontLeftISR()
    {
        handleTransition(&frontLeftState, frontLeftPins);
    }

    void ARDUINO_ISR_ATTR frontRightISR()
    {
        handleTransition(&frontRightState, frontRightPins);
    }

    void ARDUINO_ISR_ATTR rearLeftISR()
    {
        handleTransition(&rearLeftState, rearLeftPins);
    }

    void ARDUINO_ISR_ATTR rearRightISR()
    {
        handleTransition(&rearRightState, rearRightPins);
    }

    void initializeEncoder(
        const EncoderPins& pins,
        EncoderState* state,
        void (*isr)())
    {
        pinMode(pins.pinA, INPUT);
        pinMode(pins.pinB, INPUT);

        uint8_t a = digitalRead(pins.pinA);
        uint8_t b = digitalRead(pins.pinB);

        state->previousState = (a << 1) | b;

        attachInterrupt(
            digitalPinToInterrupt(pins.pinA),
            isr,
            CHANGE
        );

        attachInterrupt(
            digitalPinToInterrupt(pins.pinB),
            isr,
            CHANGE
        );
    }
}

void Encoder::setup()
{
    initializeEncoder(
        frontLeftPins, &frontLeftState, frontLeftISR);

    initializeEncoder(
        frontRightPins, &frontRightState, frontRightISR);

    initializeEncoder(
        rearLeftPins, &rearLeftState, rearLeftISR);

    initializeEncoder(
        rearRightPins, &rearRightState, rearRightISR);
}

long Encoder::getCount(Motor::MotorId motorId)
{
    EncoderState* state = getState(motorId);

    if (state == nullptr)
        return 0;

    portENTER_CRITICAL(&encoderMux);
    long count = state->count;
    portEXIT_CRITICAL(&encoderMux);

    return count;
}

void Encoder::reset(Motor::MotorId motorId)
{
    EncoderState* state = getState(motorId);

    if (state == nullptr)
        return;

    portENTER_CRITICAL(&encoderMux);
    state->count = 0;
    portEXIT_CRITICAL(&encoderMux);
}
