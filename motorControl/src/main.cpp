#include <Arduino.h>
#include "motorControl.h"

void setup() {
    pinMode(MOTOR_PIN, OUTPUT);
    pinMode(LED_PIN, OUTPUT);
    pinMode(SWITCH_PIN, INPUT);
    pinMode(PHOTO_PIN, INPUT);
}

int rampUp () {
    unsigned long startMillis = millis();
    unsigned long intervalMillis = 250;
    unsigned long previousMillis = 0;
    for (int n = MIN_CYCLE; n <= MAX_CYCLE; n++) {
        if (startMillis - previousMillis > intervalMillis) {
            analogWrite(MOTOR_PIN, n);
            previousMillis = startMillis;
        }
    }
    return 0;
}

void loop() {
    switchState = digitalRead(SWITCH_PIN);
    int rampState;
    if (switchState == HIGH) {
        rampState = rampUp();
    }
    if (rampState == 0) {
        analogWrite(MOTOR_PIN, 0);
    }
}