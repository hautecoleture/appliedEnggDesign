#include <Arduino.h>
#include <Servo.h>

#define storage A2
#define servo 5
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
Servo s1;

bool checkStorage(){                
    int avgLight = 0;
    for(int i = 0;i < 50;i++){      // Take the avg of 50 readings
        avgLight += analogRead(storage);
    }
    avgLight = avgLight/50;
    if(avgLight>110){           
        return false;
    }
    return true;
}

void flipFilter() {
    s1.write(0);
    delay(750);
    for (int i = 1; i <= 3; i++) {
        s1.write(40);
        delay(300);
        s1.write(0);
        delay(300);
    }
    delay(500);
    s1.write(180);
}

void setup() {
    Serial.begin(9600);
    if (MCUSR & _BV(BORF)) {
        Serial.println("Brown-out reset detected!");
    }
    // Clear the reset flags so you know what happens next time
    MCUSR = 0;

    s1.attach(servo);
    s1.write(180);

    pinMode(storage, INPUT);

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
            delay(3000);
            for (int i = 0; i <= 4; i++) {
                analogWrite(pwm, 0);
                delay(300);             // 0.3 sec
                digitalWrite(dir, 1);
                analogWrite(pwm, maxCycle);
                delay(300);             // 0.3 sec
                analogWrite(pwm, 0);
                delay(300);             // 0.3 sec
                digitalWrite(dir, 0);
                analogWrite(pwm, maxCycle);
                delay(3000);            // 3.0 sec
            }
            analogWrite(pwm, 0);
            grinderStatus = IDLE;
            delay(30000);
            flipFilter();
            break;
    }
}