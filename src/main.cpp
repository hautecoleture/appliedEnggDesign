#include <Arduino.h>

#define button 2
#define pwm 3
#define dir 12

// pwm vars
const int minCycle = 32;        // 1/8 max power
const int maxCycle = 255;       // 7/8 max power
const int rampInterval = 100;   // 100 ms
int currentSpeed = 0;

// state vars
bool buttonState;

// time variables
unsigned long now;
unsigned long lastRampTime;

enum GrinderState {
        IDLE,
        RAMP_UP,
        STEADY_STATE,
    };

GrinderState grinderStatus = IDLE;

void setup() {
    pinMode(pwm, OUTPUT);
    pinMode(dir, OUTPUT);
    pinMode(button, INPUT);
    lastRampTime = 0;       // setting ref point
}

void loop() {
    now = millis();         // setting time
    buttonState = digitalRead(button);

    switch(grinderStatus) {

        case IDLE:          // do nothing
            if (buttonState == HIGH) {
                lastRampTime = now;
                grinderStatus = RAMP_UP;
            } else {
                currentSpeed = 0;
                analogWrite(pwm, currentSpeed);
            }

            break;
        
        case RAMP_UP:       // pwm up
            if (now - lastRampTime >= rampInterval) {
                lastRampTime = now;
                currentSpeed += 25;
                analogWrite(pwm, currentSpeed);
            } 

            if (currentSpeed >= maxCycle) {
                grinderStatus = STEADY_STATE;
            }
            
            break;

        case STEADY_STATE:  // hold constant speed
            for (int n = 0; n <= 4; n++) {
                analogWrite(pwm, 0);
                digitalWrite(dir, 1);
                analogWrite(pwm, maxCycle);
                delay(250);
                analogWrite(pwm, 0);
                digitalWrite(dir, 0);
                analogWrite(pwm, maxCycle);
                delay(2500);
            }
            grinderStatus = IDLE;
            
            break;
    }
}