#pragma once

class Item {
public:
    Item(const char *name, int qty);
    void restQty();
    const char * getName();
    int getQty();

private:
    int quantity;
    const char *id;

    void resetQty();
};