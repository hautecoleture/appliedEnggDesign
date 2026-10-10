#ifndef GRINDER_CONTROL_HPP
#define GRINDER_CONTROL_HPP

#include <Arduino.h>

// pins
const byte BUTTON_PIN = 2;
const byte GRINDER_PIN = 3;

// pwm constants & variables      
const int MIN_CYCLE = 32;       // 1/8 max power
const int MAX_CYCLE = 224;      // 7/8 max power
const int RAMP_INTERVAL = 100;  // 100 ms
int currentSpeed = 0;           // idle

// state variables
bool buttonState;

// time variables
unsigned long now;
unsigned long lastRampTime;

// grinder states
enum GrinderState {
        IDLE,
        RAMP_UP,
        STEADY_STATE,
    };

#endif