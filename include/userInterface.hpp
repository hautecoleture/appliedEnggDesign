#ifndef USER_INTERFACE_HPP
#define USER_INTERFACE_HPP

#include <Arduino.h>
#include <LiquidCrystal.h>

const byte DATA_7 = 2;
const byte DATA_6 = 4;
const byte DATA_5 = 5;
const byte DATA_4 = 7;
const byte RS = 8;
const byte EN = 11;

LiquidCrystal lcd(RS, EN, DATA_4, DATA_5, DATA_6, DATA_7);

#endif