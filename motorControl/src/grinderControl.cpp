#include <Arduino.h>
#include <grinderControl.hpp>

void setup() {
    pinMode(GRINDER_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT);
    pinMode(CURRENT_SENSING, INPUT);
}

GrinderState grinderStatus = IDLE;

void loop() {
    now = millis();
    lastRampTime = 0;
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
                analogWrite(GRINDER_PIN, MAX_CYCLE);
                grinderStatus = STEADY_STATE;
            }
            break;

        case STEADY_STATE:  // hold constant speed
            delay(2000);    // 2 sec, fix later, blocking
            grinderStatus = IDLE;
            break;
    }
}