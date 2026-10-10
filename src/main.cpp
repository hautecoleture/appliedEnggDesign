#include <Arduino.h>
#include <grinderControl.hpp>

const int MOTOR_DIR = 12;

void setup() {
    pinMode(GRINDER_PIN, OUTPUT);
    pinMode(MOTOR_DIR, OUTPUT);
    pinMode(BUTTON_PIN, INPUT);
    lastRampTime = 0;       // setting ref point
}

GrinderState grinderStatus = IDLE;

void loop() {
    now = millis();         // setting time
    buttonState = digitalRead(BUTTON_PIN);

    switch(grinderStatus) {

        case IDLE:          // do nothing
            if (buttonState == HIGH) {
                lastRampTime = now;
                grinderStatus = RAMP_UP;
            } else {
                currentSpeed = 0;
                analogWrite(GRINDER_PIN, currentSpeed);
            }

            break;
        
        case RAMP_UP:       // pwm up
            if (now - lastRampTime >= RAMP_INTERVAL) {
                lastRampTime = now;
                currentSpeed += 25;
                analogWrite(GRINDER_PIN, currentSpeed);
            } 

            if (currentSpeed >= MAX_CYCLE) {
                grinderStatus = STEADY_STATE;
            }
            
            break;

        case STEADY_STATE:  // hold constant speed
            for (int n = 0; n <= 4; n++) {
                analogWrite(GRINDER_PIN, 0);
                digitalWrite(MOTOR_DIR, 1);
                analogWrite(GRINDER_PIN, MAX_CYCLE);
                delay(250);
                analogWrite(GRINDER_PIN, 0);
                digitalWrite(MOTOR_DIR, 0);
                analogWrite(GRINDER_PIN, MAX_CYCLE);
                delay(2500);
            }
            grinderStatus = IDLE;
            
            break;
    }
}