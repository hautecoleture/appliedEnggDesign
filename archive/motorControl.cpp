#include <Arduino.h>

// pin constants
const byte BUTTON_PIN = 2;
const byte MOTOR_PIN = 3;
const byte LED_PIN = 7;
const byte CURRENT = A0;
const byte PHOTO_PIN = A2;

// duty cycle constants
const int START_CYCLE = 50; 	// ~20% 
const int MAX_CYCLE = 250;		// ~98%
const int RAMP_MS = 1000;		// 1 second 

// state constants and variables 
const int PHOTO_MIN = 200;		// determined experimentally
int currentLevel = 0;
int photoState = 0;
bool buttonState = LOW;

void setup() {
	Serial.begin(9600);
	pinMode(MOTOR_PIN, OUTPUT);	
	pinMode(BUTTON_PIN, INPUT);
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
	buttonState = digitalRead(BUTTON_PIN);		
	photoState = analogRead(PHOTO_PIN);
	currentLevel = analogRead(CURRENT);
	Serial.println(currentLevel);
	unsigned long maxTime = 2000;
	unsigned long currentTime = millis();
	switch (photoState) {
		case 0 ... PHOTO_MIN:
			digitalWrite(LED_PIN, LOW);
			if (buttonState == HIGH) {
				analogWrite(MOTOR_PIN, MAX_CYCLE);
			} 
			else {
				stopMotor();
			}
			break;

		case PHOTO_MIN + 1 ... 1000:
			digitalWrite(LED_PIN, HIGH);
			break;

		default:
			digitalWrite(LED_PIN, HIGH);
	}
}