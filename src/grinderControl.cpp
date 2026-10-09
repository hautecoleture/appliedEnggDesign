#include <Arduino.h>
#include <grinderControl.hpp>
#include <Versatile_RotaryEncoder.h>

const int MOTOR_DIR = 12;

#define clk 24
#define dt 22
#define sw 23

void handleRotate(int8_t rotation);
void handlePressRotate(int8_t rotation);
void handleHeldRotate(int8_t rotation);
void handlePress();
void handleDoublePress();
void handlePressRelease();
void handleLongPress();
void handleLongPressRelease();
void handlePressRotateRelease();
void handleHeldRotateRelease();

Versatile_RotaryEncoder *versatile_encoder;

void setup() {
    Serial.begin(9600);
    pinMode(GRINDER_PIN, OUTPUT);
    pinMode(MOTOR_DIR, OUTPUT);
    pinMode(BUTTON_PIN, INPUT);
    // pinMode(I_SENSE_PIN, INPUT);
    lastRampTime = 0;   // setting ref point
    grindTime = 5000;   // 5 seconds

    versatile_encoder = new Versatile_RotaryEncoder(clk, dt, sw);

    // Load to the encoder all nedded handle functions here (up to 9 functions)
    versatile_encoder->setHandleRotate(handleRotate);
    versatile_encoder->setHandlePressRotate(handlePressRotate);
    versatile_encoder->setHandleHeldRotate(handleHeldRotate);
    versatile_encoder->setHandlePress(handlePress);
    versatile_encoder->setHandleDoublePress(handleDoublePress);
    //versatile_encoder->setHandleDoublePress(nullptr); // Disables Double Press
    versatile_encoder->setHandlePressRelease(handlePressRelease);
    versatile_encoder->setHandleLongPress(handleLongPress);
    versatile_encoder->setHandleLongPressRelease(handleLongPressRelease);
    versatile_encoder->setHandlePressRotateRelease(handlePressRotateRelease);
    versatile_encoder->setHandleHeldRotateRelease(handleHeldRotateRelease);

    Serial.println("Ready!");

    // set your own defualt values (optional)
    // versatile_encoder->setInvertedSwitch(true); // inverts the switch behaviour from HIGH to LOW to LOW to HIGH
    // versatile_encoder->setReadIntervalDuration(1); // set 2ms as long press duration (default is 1ms)
    // versatile_encoder->setShortPressDuration(35); // set 35ms as short press duration (default is 50ms)
    // versatile_encoder->setLongPressDuration(550); // set 550ms as long press duration (default is 1000ms)
    // versatile_encoder->setDoublePressDuration(350); // set 350ms as double press duration (default is 250ms)
}

GrinderState grinderStatus = IDLE;

void loop() {

    versatile_encoder->ReadEncoder();   // polls encoder and fires handlers

    now = millis();     // setting time
    // unsigned long lastGrindTime = 0;
    
    buttonState = digitalRead(BUTTON_PIN);      // allows for reading of the
    // rawADC = analogRead(I_SENSE_PIN);           // current sening pin in a 
    // voltageReading = rawADC*ADC_2_V;            // format that is friendly for
    // currentReading = voltageReading * V_2_mA;   // testing and troubleshooting

    switch(grinderStatus) {

        case IDLE:          // do nothing
            if (buttonState == HIGH) {
                Serial.print("Button State:     ");
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
                Serial.print("PWM:    ");
                Serial.println(currentSpeed);
            } 

            if (currentSpeed >= MAX_CYCLE) {
                grinderStatus = STEADY_STATE;
                Serial.println("Reached steady state");
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

void handleRotate(int8_t rotation) {
	Serial.print("#1 Rotated: ");
    if (rotation > 0)
	    Serial.println("Right");
    else
	    Serial.println("Left");
}

void handlePressRotate(int8_t rotation) {
	Serial.print("#2 Pressed and rotated: ");
    if (rotation > 0)
	    Serial.println("Right");
    else
	    Serial.println("Left");
}

void handleHeldRotate(int8_t rotation) {
	Serial.print("#3 Held and rotated: ");
    if (rotation > 0)
	    Serial.println("Right");
    else
	    Serial.println("Left");
}

void handlePress() {
	Serial.println("#4.1 Pressed");
}

void handleDoublePress() {
	Serial.println("#4.2 Double Pressed");
}

void handlePressRelease() {
	Serial.println("#5 Press released");
}

void handleLongPress() {
	Serial.println("#6 Long pressed");
}

void handleLongPressRelease() {
	Serial.println("#7 Long press released");
}

void handlePressRotateRelease() {
	Serial.println("#8 Press rotate released");
}

void handleHeldRotateRelease() {
	Serial.println("#9 Held rotate released");
}