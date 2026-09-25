/*
Changed data types. 

-- 	SWITCH_PIN and MOTOR_PIN are now `byte` for memory efficiency, since they 
	take up 1 byte. `int` data types take up 2 bytes of memory.
-- 	switchState is now `bool` data type for memory efficiency for the same 
	reason as above. Arduino.h defines HIGH and LOW as 1 and 0. 
*/

#include "Arduino.h"		// arduino header

const byte SWITCH_PIN = 2;	// reads signal from button
const byte MOTOR_PIN = 9;	// controls gate on MOSFET
bool switchState = 0;		// variable for switch state

void setup() {
	pinMode(MOTOR_PIN, OUTPUT);
	pinMode(SWITCH_PIN, INPUT);
}

void loop() {
	// sets switchState to match button
	switchState = digitalRead(SWITCH_PIN);

	// high on gate when switch pressed
	if (switchState == HIGH) {
		digitalWrite(MOTOR_PIN, HIGH);
		delay(2000);		// two seconds
	}

	// low on gate otherwise
	else {
		digitalWrite(MOTOR_PIN, LOW);	
	}
}