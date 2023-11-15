/*
*       A simple machine implementation for WALL-E Project
*       
*           - Lambertini Gustavo Marcos
*           - Freile Tomas
*           - Gismondi Maximo
*/
#include <Arduino.h>
#include "wifi/wifi_ruts.h"
#include "mqtt/mqtt.h"
#include "transaction.h"
#include "buffer.h"
#include "hardware/hw.h"
#include "content.h"
#include "item.h"
#include <string.h>

int board;
int id = 1;
bool try_again = true;
Buffer buffy(BUFFER_SIZE);
Content stock(CONTENT_SIZE);

void init_machine(){
    board = get_board_num();
    stock.addItem(Item("ruler", 3));
    stock.addItem(Item("pen", 3));
    stock.addItem(Item("agenda", 1));
}

void dispense(const char *topic, const char *msg){
    if(stock.hasStock(topic)){
        if(is_connected_wifi()){ //if is connected, just publish
            do_publish(topic, msg);
            delay(1000);
            Serial.println();
            Serial.println("Checking 4 Buffy");
            delay(700);
            if(!buffy.isEmpty()){ //checks buffy
                Serial.println("-----------------------------");
                Serial.println("Publishing buffy's content: ");
                buffy.publishContent();
                Serial.println("-----------------------------");
                buffy = Buffer(BUFFER_SIZE);
            } //ends transaction
            else{
                Serial.println("No elements in buffy");
            }
            try_again = true;
            stock.restItemQty(topic);
            Serial.println("Now there are: ");
            Serial.println(stock.getItem(topic).getQty());
            status_ok();
            greet_human();
        }
        else{ //if there is no wifi
            if(try_again){ //try once more
                Serial.println("trys once more");
                connect_wifi();
                init_mqtt(board);
                try_again = false;
                dispense(topic, msg);
            }
            else{//opps no wifi at all, so buffy time!!!
                Serial.println("Sending transaction into buffy");
                Transaction transaction = Transaction(topic, msg, id);
                id = id + 1; 
                buffy.addTransaction(transaction);
                try_again = true;
                
                stock.restItemQty(topic);
                Serial.println("Now there are: ");
                Serial.println(stock.getItem(topic).getQty());
                status_ok();
                greet_human();
            }
        } //rest items
    }
    else{
        Serial.println("No more stock for such item: ");
        Serial.println(topic);
        status_not_ok();
    }
}


void publishItemQty(char *topic){
    if(stock.hasItem(topic)){
        Serial.println("Sending qry info...");
        std::string result = std::string(" items") + topic;
        do_publish("qty", std::to_string(stock.getItem(topic).getQty()).c_str());
    }
    else{
        Serial.println("Could not send data");
    }
}

void new_stock(){
    stock = Content(CONTENT_SIZE);
    stock.addItem(Item("ruler", 3));
    stock.addItem(Item("pen", 3));
    stock.addItem(Item("agenda", 1));
}

void fill_machine(){
    if(!buffy.isEmpty()){ //there are transactions!!
        if(!is_connected_wifi()){
            while(!is_connected_wifi()){ //Wont stop until connects wifi
                connect_wifi();
            }
            init_mqtt(board);
        }//publish buffys transactions
        Serial.println("Publishing buffy's content: "); 
            for (Transaction transaction : buffy.getTransactions()){
                   do_publish(transaction.getTopic(), transaction.getMsg());             
            }
    }//reset machine
    buffy = Buffer(BUFFER_SIZE);
    id = 1;
    new_stock();
    fill();
}


