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
bool try_again = true;
Buffer buffy(BUFFER_SIZE);
Content stock(CONTENT_SIZE);

void init_machine(){
    board = get_board_num();
    stock.addItem(Item("ruler", 5));
    stock.addItem(Item("pen", 5));
    stock.addItem(Item("agenda", 1));
    Serial.println(stock.getItem("pen").getQty());
}

void dispense(const char *topic, const char *msg){
    if(stock.hasStock(topic)){
        if(is_connected_wifi()){ //if is connected, just publish
            do_publish(topic, msg);
            if(!buffy.isEmpty()){ //checks buffy
                Serial.print("Publishing buffy's content: ");
                for (Transaction transaction : buffy.getTransactions()){
                    do_publish(transaction.getTopic(), transaction.getMsg());
                }
            } //ends transaction
        }
        else{ //if there is no wifi
            if(try_again){ //try once more
                connect_wifi();
                init_mqtt(board);
                dispense(topic, msg);
                try_again = false;
            }
            else{//opps no wifi at all, so buffy time!!!
                Transaction transaction = Transaction(topic, msg); 
                buffy.addTransaction(transaction);
                try_again = true;
            }
            
        } //rest items
        stock.restItemQty(topic);
        Serial.print("Now there are: ");
        Serial.print(stock.getItem(topic).getQty());
        Serial.printf("Send into bufffy, wifi connection error");            
        status_ok();
        greet_human();
    }
    else{
        Serial.print("No more stock for such item: ");
        Serial.print(msg);
        status_not_ok();
    }
}


void publishItemQty(char *topic){
    if(stock.hasItem(topic)){
        std::string result = std::string(" items") + topic;
        do_publish("qty", std::to_string(stock.getItem(topic).getQty()).c_str());
    }
}

void fill_machine(){
    if(!buffy.isEmpty()){ //there are transactions!!
        if(!is_connected_wifi()){
            while(!is_connected_wifi()){ //Wont stop until connects wifi
                connect_wifi();
            }
            init_mqtt(board);
        }//publish buffys transactions
        Serial.print("Publishing buffy's content: "); 
            for (Transaction transaction : buffy.getTransactions()){
                   do_publish(transaction.getTopic(), transaction.getMsg());             
            }
    }//reset machine
    buffy.clearBuffer();
    init_machine();
    fill();
}