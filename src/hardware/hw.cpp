/*
 *  Project 41-mqtt_00 - Austral - EAM
 *
 *  hw.cpp
 *      Hardware dependent code
 */

#include <Arduino.h>

#include "hw.h"
/*
 *  get_board_num
 *      Return board number read from IB1,IB0
 */


int
get_board_num(void)
{
    return digitalRead(IB0) | (digitalRead(IB1) << 1); 
}

/*
 *  init_hw
 *      Called at power up
 */

void
init_hw(void)
{
    pinMode(IB0,INPUT_PULLUP);
    pinMode(IB1,INPUT_PULLUP);

    pinMode(PEN, INPUT_PULLDOWN);       //Buttons for dispense
    pinMode(RULER, INPUT_PULLDOWN);
    pinMode(FILL, INPUT_PULLDOWN);
    pinMode(SELL_LED, OUTPUT);
    
    pinMode(GREET, OUTPUT); //ISD1820 PLAY-E
    pinMode(GREET_LED, OUTPUT); 
}

/*
 *  verify_hw
 *      Verifies all input hardware
 */

void
greet_human(){
    digitalWrite(GREET_LED, HIGH);
    digitalWrite(GREET, HIGH);
    delay(2000);
    digitalWrite(GREET, LOW);
    digitalWrite(GREET_LED, LOW);
}

void 
fill(){
    digitalWrite(SELL_LED, HIGH);
    delay(1000);
    digitalWrite(SELL_LED, LOW);
    digitalWrite(GREET_LED, HIGH);
    delay(1000);
    digitalWrite(GREET_LED, LOW);
    delay(500);
    status_ok();
}

void
status_ok(){
    digitalWrite(SELL_LED, HIGH);
    digitalWrite(GREET_LED, HIGH);
    delay(700);
    digitalWrite(SELL_LED, LOW);
    digitalWrite(GREET_LED, LOW);
    delay(700);
    status_ok();
}

void
status_not_ok(){
    int counter = 0;
    while(counter != 5){
        digitalWrite(SELL_LED, HIGH);
        delay(500);
        digitalWrite(SELL_LED, LOW);
        counter = counter + 1;
    }
}
