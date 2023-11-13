#pragma once

void init_machine();
void dispense(const char *topic, const char *msg);
void publishItemQty(char *topic);
void fill_machine();