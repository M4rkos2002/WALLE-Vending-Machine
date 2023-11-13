#include "item.h"

Item::Item(const char *name, int qty){
    id = name;
    quantity = qty;
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

