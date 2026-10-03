#include <Arduino.h>
#include <Servo.h>

Servo s1;

#define servoPin 10


void flipFilter(){//Flip the filter and place it back
    s1.write(0);
    delay(500);
    s1.write(180);
}

void setup(){
    Serial.begin(115200);
    s1.attach(servoPin);
}

void loop(){
    s1.write(180);
    delay(1000);
    flipFilter();
    while(false){}
}