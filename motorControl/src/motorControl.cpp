#include "Arduino.h"		// arduino header

const int switchPin = 2;	// reads signal from button
const int motorPin = 9;		// controls gate on MOSFET
int switchState = 0;		// variable for switch state

void setup() {
	pinMode(motorPin, OUTPUT);
	pinMode(switchPin, INPUT);
}

void loop() {
	// sets switchState to match button
	switchState = digitalRead(switchPin);

	// high on gate when switch pressed
	if (switchState == HIGH) {
		digitalWrite(motorPin, HIGH);	
	}

	// low on gate otherwise
	else {
		digitalWrite(motorPin, LOW);	
	}
}