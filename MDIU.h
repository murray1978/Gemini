/*
 * MDIU.h
 *  Both MDK (Modular Display Keyboard) and MDR (Modular Display Readout are implimented here
*/
#pragma once
#include <keypad.h>
#include "LED_Display.h"

const byte ROWS = 4; // Four rows
const byte COLS = 3; // Three columns

char keys[ROWS][COLS] = 
{{'1','2','3'},
 {'4','5','6'},
 {'7','8','9'},
 {'*','0','#'}};

byte rowPins[ROWS] = { 5,4,3,2 };
byte colPins[COLS] = { 8,7,6 };
byte led_DIN = 9;
byte led_CS = 10;
byte led_CLK = 11;
 
int count = 0;

/*
 * Prefer camel case, but ....
 * In the escence of readability I will use undeerscore..
*/
char MDIU_Register[7];
Keypad MDIU_Keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
LED_Display MDIU_Display = LED_Display( led_DIN, led_CS, led_CLK );


//char key = keypad.getKey();
//if( key != NO_KEY )



