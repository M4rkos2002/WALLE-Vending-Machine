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
    stock.addItem(Item("ruler", 3));
    stock.addItem(Item("pen", 3));
}

void dispense(const char *topic, const char *msg){
    if(stock.hasStock(topic)){
        if(is_connected_wifi()){ //if is connected, just publish
            do_publish(topic, msg);
            if(!buffy.isEmpty()){ //checks buffy
                Serial.println("Publishing buffy's content: ");
                for (Transaction transaction : buffy.getTransactions()){
                    do_publish(transaction.getTopic(), transaction.getMsg());
                }
                buffy = Buffer(BUFFER_SIZE);
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
        Serial.println("Now there are: ");
        Serial.println(stock.getItem(topic).getQty());
        status_ok();
        greet_human();
    }
    else{
        Serial.println("No more stock for such item: ");
        Serial.println(topic);
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
        Serial.println("Publishing buffy's content: "); 
            for (Transaction transaction : buffy.getTransactions()){
                   do_publish(transaction.getTopic(), transaction.getMsg());             
            }
    }//reset machine
    buffy = Buffer(BUFFER_SIZE);
    new_stock();
    fill();
}

void new_stock(){
    stock = Content(CONTENT_SIZE);
    stock.addItem(Item("ruler", 3));
    stock.addItem(Item("pen", 3));
    stock.addItem(Item("agenda", 1));
}
