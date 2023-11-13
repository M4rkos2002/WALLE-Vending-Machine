/*
|    A simple Transaction implementation for WALL-E Project
|
|          - Lambertini Gustavo Marcos
|          - Freile Tomás
|          - Gismondi Máximo
|
*/

#include "transaction.h"

Transaction::Transaction(const char *topic, const char *message) {  //constructor implementation for struct
        this->topic = topic;
        this->message = message;
}

const char * Transaction::getMsg(){
        return message;
}

const char * Transaction::getTopic(){
        return topic;
}