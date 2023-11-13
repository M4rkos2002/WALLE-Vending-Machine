#pragma once

#include <vector>  
#include "transaction.h"
#include "mqtt/mqtt.h"


class Buffer {
public:

    Buffer(int max_size);
    void addTransaction(const Transaction& transaction);
    void publishContent();
    std::vector<Transaction> getTransactions();
    bool isEmpty();
    bool isFull();
    int getMaxSize();
    void clearBuffer();

private:
    std::vector<Transaction> transactions;
    int max_size;

};
