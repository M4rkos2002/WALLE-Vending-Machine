#include "item.h"

Item::Item(){
    this->id = "";
    this->quantity = 0;
}

Item::Item(const char *name, int qty){
    this->id = name;
    this->quantity = qty;
}

void Item::restQty(){
    quantity = quantity - 1;
}

const char * Item::getName(){
    return id;
}

int Item::getQty(){
    return quantity;
}

