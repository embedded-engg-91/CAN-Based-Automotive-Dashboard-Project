#include <xc.h>
#include <string.h>
#include "message_handler.h"
#include "msg_id.h"
#include "can.h"
#include "clcd.h"
#include "uart.h"
#include <stdint.h>

void handle_speed_data(uint8_t *data, uint8_t len) {

    clcd_print(data, LINE1(3));
}

void handle_gear_data(uint8_t *data, uint8_t len) {
    //Implement the gear function
    unsigned char ch = *data;
    clcd_putch(' ', LINE1(9));
    clcd_putch(' ', LINE1(10));
    clcd_putch(' ', LINE1(11));
    clcd_putch(ch + '0', LINE1(9));
}

void handle_rpm_data(uint8_t *data, uint8_t len) {

    clcd_putch(' ', LINE2(2));
    clcd_putch(' ', LINE2(3));
    clcd_putch(' ', LINE2(4));
    clcd_putch(' ', LINE2(5));

    clcd_print(data, LINE2(2));
}

void handle_engine_temp_data(uint8_t *data, uint8_t len) {
    //Implement the temperature function
    clcd_print(data, LINE2(10));

}

void handle_indicator_data(uint8_t *data, uint8_t len) {
    //Implement the indicator function
    if (len == 0) clcd_putch('O', LINE1(14)); //indicator off
    clcd_putch(data[0] + '0', LINE1(14));
}

void process_canbus_data() {


    uint16_t msg_id = 0;
    char buffer[8] = {0}; //must to initialise 
    uint8_t rx_str_len = 0;
    can_receive(&msg_id, (uint8_t *) buffer, &rx_str_len);
    if (rx_str_len > 0 && rx_str_len <= 8) {//if valid length only then enter    
        buffer[rx_str_len] = '\0';
        switch (msg_id) {
            case SPEED_MSG_ID:
                handle_speed_data((uint8_t *) buffer, rx_str_len);
                break;

            case GEAR_MSG_ID:
                handle_gear_data((uint8_t *) buffer, rx_str_len);
                break;

            case RPM_MSG_ID:
                handle_rpm_data((uint8_t *) buffer, rx_str_len);
                break;

            case ENG_TEMP_MSG_ID:
                handle_engine_temp_data((uint8_t *) buffer, rx_str_len);
                break;

            case INDICATOR_MSG_ID:
                handle_indicator_data((uint8_t *) buffer, rx_str_len);
                break;

            default:
                break;
        }
    }
}