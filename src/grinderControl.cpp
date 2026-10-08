#include <Arduino.h>
#include <Servo.h>
#include <grinderControl.hpp>

Servo s1;

const int SERVO = 10;

void setup() {
    Serial.begin(9600);
    s1.attach(SERVO_PIN);
    pinMode(GRINDER_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT);
    pinMode(I_SENSE_PIN, INPUT);
    
}

// void flipFilter(){//Flip the filter and place it back
//     s1.write(0);
//     delay(2000);
//     s1.write(180);
// }

GrinderState grinderStatus = IDLE;

void loop() {
    now = millis();     // setting time
    lastRampTime = 0;   // setting ref point
    buttonState = digitalRead(BUTTON_PIN);      // allows for reading of the
    rawADC = analogRead(I_SENSE_PIN);           // current sening pin in a 
    voltageReading = rawADC*ADC_2_V;            // format that is friendly for
    currentReading = voltageReading * V_2_mA;   // testing and troubleshooting

    // s1.write(180);
    // delay(1000);
    // flipFilter();
    // while(false){}
    // Serial.print("\033[2K\rCurrent (mA):   ");
    Serial.print("\rGrind time:   ");
    // Serial.print(currentReading);

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
            grindTime = now;
            delay(5000);
            grinderStatus = IDLE;
            Serial.print(now - grindTime);
            // if (now - grindTime >= 2000) {
            //     grinderStatus = IDLE;
            // }
            break;
    }

    // if (currentReading = 2000) {
    //     grinderStatus = IDLE;
    //     Serial.println("2A reached! Stopping process.");
    // }
}