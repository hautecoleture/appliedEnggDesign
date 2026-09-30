#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include <Arduino.h>

// pins
const byte SWITCH_PIN = 2;
const byte MOTOR_PIN = 3;
const byte LED_PIN = 7;
const byte PHOTO_PIN = A0;
const byte CURRENT_SENSING = A2;

// duty cycle
const int MIN_CYCLE = 50;
const int MAX_CYCLE = 250;

// photo sensor
const int PHOTO_MIN = 200;

// state variables
int photoState;
bool switchState;

// rampUp function
void rampUp (
    unsigned long startMillis,
    unsigned long previousMillis,
    unsigned long interval
);

void constantSpeed ();

#endif