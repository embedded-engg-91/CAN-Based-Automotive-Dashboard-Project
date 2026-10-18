#include "adc.h"
#include "can.h"
#include "ecu1_sensor.h"
#include "msg_id.h"
#include "uart.h"
#include <stdio.h>

void init_config() {
    init_can();
    init_adc();
    init_digital_keypad();

}

int main() {
    init_config();
    
    char str[100];
    while (1) {
        get_speed();    
        get_gear_pos(); 

    }
}
