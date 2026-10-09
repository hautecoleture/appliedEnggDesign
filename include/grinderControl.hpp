#ifndef GRINDER_CONTROL_HPP
#define GRINDER_CONTROL_HPP

#include <Arduino.h>

// pins
const byte BUTTON_PIN = 13;
const byte GRINDER_PIN = 3;
const byte I_SENSE_PIN = A0;

// pwm constants & variables      
const int MIN_CYCLE = 32;       // 1/8 max power
const int MAX_CYCLE = 224;      // 7/8 max power
const int RAMP_INTERVAL = 200;  // 100 ms
int currentSpeed = 0;           // idle

// sensing constants & variables
const float ADC_2_V = 1023/5;   // 10-bit ADC, 5V ref
const float V_2_mA = 1.65/1000; // 1.65 V/A, 1000 mA per A
float rawADC;
float voltageReading;
float currentReading;

// state variables
bool buttonState;

// time variables
unsigned long now;
unsigned long lastRampTime;
unsigned long grindTime;

// grinder states
enum GrinderState {
        IDLE,
        RAMP_UP,
        STEADY_STATE,
    };

#endif