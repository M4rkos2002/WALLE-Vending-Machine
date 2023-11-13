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
    //TelnetStream.begin();
}

void loop(void)
{
    if(digitalRead(PEN) == HIGH){               //Dispense pen
        Serial.print("dispenso una lapicera");
        dispense("pen", "sacá una lapicera");
        delay(1000);
    }

    else if(digitalRead(RULER) == HIGH){        //Dispense ruler
        Serial.print("dispenso una regla");
        dispense("ruler", "sacá una regla");
        delay(1000);
    }

    else if(digitalRead(FILL) == HIGH){
        Serial.print("Reiniciando contenido");
        fill_machine();
        delay(1000);
    }

}
