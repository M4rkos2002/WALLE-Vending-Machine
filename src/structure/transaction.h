#pragma once

struct Transaction{
    const char *topic;
    const char *message;

    Transaction(const char *topic, const char *message);
    const char * getMsg();
    const char * getTopic();
};