#include <Arduino.h>
#include <userInterface.hpp>

void setup() {
    Serial.begin(9600);
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    
    // Print a message to the LCD.
}

void loop() {
    Serial.print("\r");
    Serial.print("Nothing");
    lcd.setCursor(0,1);
    lcd.print("FBGM.");
}