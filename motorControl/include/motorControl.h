#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include <Arduino.h>

// pins
const byte SWITCH_PIN = 2;
const byte MOTOR_PWM_PIN = 3;
const byte CURRENT_SENSING = A0;

// duty cycle               // I would not rec exceeding 7/8 max power
const int MIN_CYCLE = 32;   // 1/8 max power
const int MAX_CYCLE = 224;  // 7/8 max power

// state variables
int photoState;
bool switchState;

// time variables
unsigned long now;
unsigned long prev;

#endif