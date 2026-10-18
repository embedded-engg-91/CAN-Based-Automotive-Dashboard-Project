#include <xc.h>
#include <stdint.h>
#include "can.h"
#include "clcd.h"
#include "msg_id.h"
#include "message_handler.h"
#include "timer0.h"

static void init_leds() {
    TRISB = 0x08; 
    PORTB = 0x00;
}

static void init_config(void) {
    
    init_clcd();
    init_can();
    init_leds();

   
}

void main(void) {
    
    init_config();

    while (1) {
        
        clcd_print("SP:", LINE1(0));
        clcd_print("G:", LINE1(7));
        clcd_print("I:", LINE1(12));
        clcd_print("R:", LINE2(0));
        clcd_print("T:", LINE2(8));

        process_canbus_data();


    }

    return;
}
