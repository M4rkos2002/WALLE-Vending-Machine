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

const double sound_speed = 0.0343;

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

    else if(digitalRead(AGENDA) == HIGH){       //Dispense agenda
        Serial.println("Dispending a agenda");
        dispense("agenda", "agenda dispensed");
    }

    else if(digitalRead(FILL) == HIGH){
        Serial.println("Filling . . . . (°c_°)");
        fill_machine();
    }

    test_mqtt();

    //long duration;
    //double distance;

    //send_trigger();
    //duration = get_pulse();

   // distance = (duration * sound_speed) / 2;
  //  Serial.println("Distance: ");
  //  Serial1.print(distance);

  //  if(distance > 1){
    //    Serial.println("Strange movement");
      //  do_publish("move", "Earthquake in Walle's position");
    //}

}
