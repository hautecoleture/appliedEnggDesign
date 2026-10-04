#include <Arduino.h>
#include <motorControl.h>
#include <grinderStates.hpp>

// these are defined in motorControl.h
void setup() {
    pinMode(MOTOR_PWM_PIN, OUTPUT);
    pinMode(SWITCH_PIN, INPUT);
    pinMode(CURRENT_SENSING, INPUT);
}

GrinderState currentState = IDLE;
unsigned long lastRamp = 0;
int rampInterval = 100;      // 50 ms
int currentPWM = 0;

void loop() {
    now = millis();
    switchState = digitalRead(SWITCH_PIN);

    switch(currentState) {

        case IDLE:
            if (switchState == HIGH) {
                lastRamp = now;
                currentState = RAMP_UP;
            } else {
                currentPWM = 0;
                analogWrite(MOTOR_PWM_PIN, currentPWM);
            }
            break;
        
        case RAMP_UP:
            if (now - lastRamp >= rampInterval) {
                lastRamp = now;
                currentPWM += 25;
                analogWrite(MOTOR_PWM_PIN, currentPWM);
            } 

            if (currentPWM >= MAX_CYCLE) {
                analogWrite(MOTOR_PWM_PIN, MAX_CYCLE);
                currentState = STEADY_STATE;
            }
            break;

        case STEADY_STATE:
            delay(2000);    // 2 sec, fix later, blocking
            currentState = IDLE;
            break;
    }
}