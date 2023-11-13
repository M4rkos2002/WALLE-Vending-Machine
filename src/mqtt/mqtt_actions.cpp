#include <TelnetStream.h>
#include "mqtt_actions.h"
#include "structure/machine_actions.h"

extern int board;

void publish_itemQty( int origin, char *item_id ){
    TelnetStream.printf("%02d -> %02d |  %s: msg -> %s\n", origin, board, __FUNCTION__, item_id );
    publishItemQty(item_id);
};
