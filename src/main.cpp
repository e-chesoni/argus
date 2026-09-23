#include <iostream>
#include <Arduino.h>

#ifndef LED_BUILTIN
#define LED_BUILTIN 18  // change this if your board uses a different LED pin
#endif

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);

    Serial.begin(115200);

    // Give the USB serial connection a moment to initialize
    delay(2000);

    Serial.println("Hello world! I am Argus.");
}

void loop()
{
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("LED ON");

    delay(1000);

    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("LED OFF");

    delay(1000);
}