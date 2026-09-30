#include <Arduino.h>

// pin constants
const byte SWITCH_PIN = 2;
const byte MOTOR_PIN = 9;
const byte PHOTO_PIN = A0;
const byte LED_PIN = 7;

// duty cycle constants
const int START_CYCLE = 50; 	// ~20% 
const int MAX_CYCLE = 250;		// ~98%
const int RAMP_MS = 1000;		// 1 second 

// state constants and variables 
const int PHOTO_MIN = 25;		// determined experimentally
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


/* need to use switch...case logic here */
void loop() {
	switchState = digitalRead(SWITCH_PIN);		
	photoState = analogRead(PHOTO_PIN);

	switch (photoState) {
		case 0 ... PHOTO_MIN:	// maybe different colors for levels?
			digitalWrite(LED_PIN, LOW);

			switch (switchState) {
				case HIGH:
					rampUp();
					delay(2000);	// blocking, maybe use millis()
					stopMotor();
					break;

				default:
					stopMotor();
			}
			break;

		default:
			digitalWrite(LED_PIN, HIGH);
	}
}