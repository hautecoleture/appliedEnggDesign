#include "Arduino.h"
// pins
const byte SWITCH_PIN = 2;
const byte MOTOR_PIN = 9;		// controls gate on MOSFET
const byte PHOTO_PIN = A0;
const byte LED_PIN = 7;
// duty cycle constants
const byte START_CYCLE = 50; 	// ~20% 
const byte MAX_CYCLE = 250;		// ~98%
const int RAMP_MS = 1000;		// 1 second 
// state and comparison variables
const int PHOTO_LEVEL = 5;		// determined experimentally
int photoState = 0;
bool switchState = LOW;

void setup() {
	pinMode(MOTOR_PIN, OUTPUT);	
	pinMode(SWITCH_PIN, INPUT);
	pinMode(PHOTO_PIN, INPUT);
	pinMode(LED_PIN, OUTPUT);
}

/* Need some logic to halt the motor if there is a jam and current spikes. 
A ramp-up prevents a dramatic current spike at the start. 
*/
void rampUp() {
	byte steps = MAX_CYCLE - START_CYCLE;
	for (byte n = START_CYCLE; n <= MAX_CYCLE; n++) {
		analogWrite(MOTOR_PIN, n);
		delay(RAMP_MS/steps);
	}
	
}

void stopMotor() {
	analogWrite(MOTOR_PIN, 0);
}

void loop() {
	switchState = digitalRead(SWITCH_PIN);		
	photoState = analogRead(PHOTO_PIN);
	// only run grinder if hopper is not low
	if (photoState < PHOTO_LEVEL) {
		digitalWrite(LED_PIN, LOW);
		// motor logic
		if (switchState == HIGH) {
			rampUp();
			delay(2000);	// two seconds
			stopMotor();
		}
		else {
			digitalWrite(MOTOR_PIN, LOW);
		} 
	} 
	else {
		digitalWrite(LED_PIN, HIGH);
	}
}