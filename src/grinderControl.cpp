#include <Arduino.h>
#include <grinderControl.hpp>

const int MOTOR_DIR = 12;

void setup() {
    // Serial.begin(9600);
    pinMode(GRINDER_PIN, OUTPUT);
    pinMode(MOTOR_DIR, OUTPUT);
    pinMode(BUTTON_PIN, INPUT);
    // pinMode(I_SENSE_PIN, INPUT);
    lastRampTime = 0;   // setting ref point
    grindTime = 5000;   // 5 seconds
}

GrinderState grinderStatus = IDLE;

void loop() {
    now = millis();     // setting time
    // unsigned long lastGrindTime = 0;
    
    buttonState = digitalRead(BUTTON_PIN);      // allows for reading of the
    // rawADC = analogRead(I_SENSE_PIN);           // current sening pin in a 
    // voltageReading = rawADC*ADC_2_V;            // format that is friendly for
    // currentReading = voltageReading * V_2_mA;   // testing and troubleshooting

    switch(grinderStatus) {

        case IDLE:          // do nothing
            if (buttonState == HIGH) {
                // Serial.print("Button State:     ");
                lastRampTime = now;
                // lastGrindTime = now;
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
                // Serial.print("PWM:    ");
                // Serial.println(currentSpeed);
            } 

            if (currentSpeed >= MAX_CYCLE) {
                grinderStatus = STEADY_STATE;
                // Serial.println("Reached steady state");
            }
            
            break;

        case STEADY_STATE:  // hold constant speed
            for (int n = 0; n <= 4; n++) {
                digitalWrite(MOTOR_DIR, 1);
                analogWrite(GRINDER_PIN, MAX_CYCLE);
                delay(250);
                digitalWrite(MOTOR_DIR, 0);
                analogWrite(GRINDER_PIN, MAX_CYCLE);
                delay(2500);
            }
            grinderStatus = IDLE;
            break;
    }
}