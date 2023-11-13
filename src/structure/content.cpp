#include "content.h"
#include <vector>
#include <string.h>


Content::Content(int max_size){
    items = std::vector<Item>();
    items.reserve(max_size); 
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
        getItem(id).restQty();
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


