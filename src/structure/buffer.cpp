
/*
|
|   A simple buffer implementation for WALL-E Project
|       
|       - Lambertini Gustavo Marcos
|       - Gismondi Maximo
|       - Freile Tomás
|
*/
#include <vector>  
#include "buffer.h"
#include "transaction.h"

Buffer::Buffer(int max_size){
    transactions = std::vector<Transaction>(); //empty buffer 
    transactions.reserve(max_size);
    
}

void Buffer::addTransaction(const Transaction& transaction) {
    if (transactions.size() <= max_size) {
            transactions.push_back(transaction);
        } else {
            while(!transactions.empty()){//                   
                publishContent(); //try publish and wont stop(°c_°)
            }                      
            addTransaction(transaction);
        }       
}

void Buffer::publishContent() {
    // Publishes all transactions  
    for (const Transaction transaction : transactions) {
        do_publish(transaction.topic, transaction.message);
    }
    clearBuffer();
}

void Buffer::clearBuffer() {
    //delete all transactions from buffer
    transactions.clear();
}

bool Buffer::isEmpty(){
    return transactions.empty();
}

bool Buffer::isFull(){
    return transactions.size() == max_size;
}

std::vector<Transaction> Buffer::getTransactions(){
    return transactions;
}

int Buffer::getMaxSize(){
    return max_size;
}