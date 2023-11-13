#pragma once
#include "item.h"
#include <vector>

class Content{
public:
    Content(int size);
    void addItem(Item item);
    void restItemQty(const char *id);
    Item getItem(const char *id);
    bool isFull();
    bool hasStock(const char *id);
    bool hasItem(const char *id);
    void clear();

private:
    std::vector<Item> items;
    int max_size;

};