#include "Arduino.h"
// motor pins
const byte SWITCH_PIN = 2;
const byte MOTOR_PIN = 9;		// controls gate on MOSFET
const byte DUTY_CYCLE = 255;	// duty cycle from 0-255, 255 is 100%
// photoresistor + LED pins
const byte PHOTO_PIN = A0;
const byte LED_PIN = 7;
// state and comparison variables
const int PHOTO_LEVEL = 50;		// determined experimentally
int photoState = 0;
bool switchState = LOW;

void setup() {
	pinMode(MOTOR_PIN, OUTPUT);	
	pinMode(SWITCH_PIN, INPUT);
	pinMode(PHOTO_PIN, INPUT);
	pinMode(LED_PIN, OUTPUT);
}

void loop() {
	switchState = digitalRead(SWITCH_PIN);		
	photoState = analogRead(PHOTO_PIN);
	// only run grinder if hopper is not low
	if (photoState < PHOTO_LEVEL) {
		digitalWrite(LED_PIN, LOW);
		// motor logic
		if (switchState == HIGH) {
			// analogWrite for PWM
			analogWrite(MOTOR_PIN, DUTY_CYCLE);
			delay(2000);	// two seconds
			digitalWrite(MOTOR_PIN, LOW);
		}
		else {
			digitalWrite(MOTOR_PIN, LOW);
		} 
	} 
	else {
		digitalWrite(LED_PIN, HIGH);
	}
}