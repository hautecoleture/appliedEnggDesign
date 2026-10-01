#include <Arduino.h>
#include "motorControl.h"

// ============================================================================
// These pins are defined as constants in motorControl.h. 
// ============================================================================
void setup() {
    pinMode(MOTOR_PIN, OUTPUT);
    pinMode(LED_PIN, OUTPUT);
    pinMode(SWITCH_PIN, INPUT);
    pinMode(PHOTO_PIN, INPUT);
}

// ============================================================================
// This function is PWM control of the motor itself. To update constants, edit 
// the motorControl.h header.
// ============================================================================
void rampUp(
    unsigned long now = millis(), 
    unsigned long prev = 0, 
    unsigned long interval = 50         // 50 ms
) {
    for (
        int n = MIN_CYCLE;
        n <= MAX_CYCLE;
        n++
    ) {
        if (now - prev >= interval) {
            analogWrite(MOTOR_PIN, n);
            prev = now;
        }
    }
}

void loop() {
    switchState = digitalRead(SWITCH_PIN);
    if (switchState == HIGH) {
        rampUp();       // PWM ramp
        analogWrite(MOTOR_PIN, MAX_CYCLE);
        delay(2000);    // 2 sec, hold on 
        analogWrite(MOTOR_PIN, 0);
        delay(2000);    // 2 sec, cool down
}