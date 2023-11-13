#include "content.h"
#include <vector>
#include <string.h>


Content::Content(int size){
    this->items = std::vector<Item>(size);
    this->max_size = size;
}

void Content::addItem(Item item){
    if(!hasItem(item.getName())){
        if(!items.empty()){
            items.push_back(item);
        }
    }
}

void Content::restItemQty(const char *id){
    if(hasItem(id)){
        std::vector<Item> newItems = std::vector<Item>(max_size);
        for(Item item:items){
            if(item.getName() == id){
                newItems.push_back(Item(id, item.getQty() - 1));
            }
            else{
                newItems.push_back(item);
            }
        }
        this->items = newItems;
    }
}

Item Content::getItem(const char *id){
    for (Item item : items){
        if(strcmp(item.getName(), id) == 0){
            return item;
        }
    }
}

bool Content::isFull(){
    return items.size() == max_size;
}

bool Content::hasItem(const char *id){
    for(Item item : items){
        if(strcmp(item.getName(), id) == 0){
            return true;
        }
    }
    return false;
}

bool Content::hasStock(const char *id){
    if(hasItem(id)){
        return getItem(id).getQty() > 0;
    }
    return false;
}

void Content::clear(){
    items.clear();
}


