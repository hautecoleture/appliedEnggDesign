/*
Changed data types. 

-- 	SWITCH_PIN and MOTOR_PIN are now `byte` for memory efficiency, since they 
	take up 1 byte. `int` data types take up 2 bytes of memory.
-- 	switchState is now `bool` data type for memory efficiency for the same 
	reason as above. Arduino.h defines HIGH and LOW as 1 and 0. 

Other changes. 
-- 	Created DUTY_CYCLE constant. Arduino UNO rev3 has a PWM frequency of 
	~500Hz. Time between rising edges is 2ms. Uses analogWrite. 
*/

#include "Arduino.h"			// arduino header

// for the motor
const byte SWITCH_PIN = 2;		// reads signal from button
const byte MOTOR_PIN = 9;		// controls gate on MOSFET
const byte DUTY_CYCLE = 255;	// duty cycle from 0-255, 255 is 100%

// for the photoresistor
const byte PHOTO_PIN = 8;		// photoresistor pin
const byte EMPTY_LED = 7;		// light for empty

// state variables
bool switchState = false;		// variable for switch state
bool isEmpty = false; 			// logic for photoresistor

void setup() {
	pinMode(MOTOR_PIN, OUTPUT);
	pinMode(SWITCH_PIN, INPUT);
}

void loop() {
	// sets switchState to match button
	switchState = digitalRead(SWITCH_PIN);
	isEmpty = digitalRead(PHOTO_PIN);

	// only run grinder if it is not empty
	if (isEmpty == false) {

		// turn off empty LED
		digitalWrite(EMPTY_LED, LOW);

		// high on gate when switch pressed, low otherwise
		if (switchState == HIGH) {
			analogWrite(MOTOR_PIN, DUTY_CYCLE);
			delay(2000);		// two seconds
		} else {
			digitalWrite(MOTOR_PIN, LOW);	
		} 
		
	} else {
		// turn on empty LED
		digitalWrite(EMPTY_LED, HIGH);
	}
}