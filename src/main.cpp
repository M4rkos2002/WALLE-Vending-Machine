/*
 *  Project 41-mqtt_00 - Austral - EAM
 *
 *      File main.cpp
 */

#include <Arduino.h>
#include <TelnetStream.h>

#include "hardware/hw.h"
#include "structure/machine_actions.h"
#include "wifi/wifi_ruts.h"
#include "mqtt/mqtt.h"


void
setup(void)
{
    Serial.begin(BAUD);
    init_hw();
    init_machine();
    connect_wifi();
    init_mqtt(get_board_num());
    TelnetStream.begin();
}

void loop(void)
{
    if(digitalRead(PEN) == HIGH){               //Dispense pen
        Serial.println("Dispending a pen");
        dispense("pen", "pen dispensed");
    }

    else if(digitalRead(RULER) == HIGH){        //Dispense ruler
        Serial.println("Dispending a ruler");
        dispense("ruler", "ruler dispensed");
    }

    else if(digitalRead(FILL) == HIGH){
        Serial.println("Filling . . . . (°c_ °)");
        fill_machine();
    }

}
