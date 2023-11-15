#pragma once

struct Transaction{
    const char *topic;
    const char *message;
    int id;

    Transaction(const char *topic, const char *message, int id);
    const char * getMsg();
    const char * getTopic();
};