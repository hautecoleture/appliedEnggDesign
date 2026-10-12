/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.

 https://docs.arduino.cc/learn/electronics/lcd-displays

*/

#include <Arduino.h>
#include <LiquidCrystal.h>


#define rs 12
#define en 11
#define d4 5
#define d5 4
#define d6 3
#define d7 2

#define enc_sw 29
#define enc_A 33
#define enc_B 37

LiquidCrystal display(rs, en, d4, d5, d6, d7);

const int numOpts = 3;
const String promptSize = "Select cup size:";
const String sizeOpts[numOpts] = {" 8 oz", "12 oz", "16 oz"};

int clkState;
int readEncoder() {
	int clk = digitalRead(enc_A);
	int dir = 0;
	if (clk != clkState && clk == LOW) {
		dir = (digitalRead(enc_B) != clk) ? 1 : -1;
	}
	clkState = clk;
	return dir;
}

int sizeSelection = 0;
void showSize() {
	display.setCursor(11, 1);
	display.print(sizeOpts[sizeSelection]);
}

void selectSize() {
	int sw_state = digitalRead(enc_sw);
	// while (sw_state == HIGH) {
		if (sw_state == LOW) {
			Serial.print("\rSelected:	");
			Serial.print(sizeOpts[sizeSelection]);
		// 	return sizeSelection;
		}
	// }
}


void setup() {
	pinMode(enc_A, INPUT);
	pinMode(enc_B, INPUT);
	pinMode(enc_sw, INPUT);

	clkState = digitalRead(enc_A);

	display.begin(16, 2);
	display.setCursor(0, 0);
	display.print(promptSize);
	showSize();

	Serial.begin(9600);
}

void loop() {
	int dir = readEncoder();
	if (dir != 0) {
		sizeSelection = (sizeSelection + dir + numOpts) % numOpts;
		showSize();
	}
	selectSize();
}
