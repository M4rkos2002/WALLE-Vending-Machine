/*
 *  Hardware header for Project WALL-E
 *
 *          - Lambertini Gustavo
 *          - Freile Tomás
 *          - Gismondi Máximo     
 * 
 */

enum
{
    NOHW, BUTTON,
    NUM_NEWS
};

void init_hw(void);         //  Called at power up
int get_board_num(void);    //  return board number
void greet_human();
void status_ok();
void status_not_ok();
void fill();
long get_pulse();           //HC-SRO4
void send_trigger();