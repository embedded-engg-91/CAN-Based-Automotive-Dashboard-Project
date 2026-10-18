#include "ecu1_sensor.h"
#include "adc.h"
#include "can.h"
#include "msg_id.h"
#include "uart.h"
#include <stdio.h>
#include <string.h>

char *gears[] = {"GN", "G1", "G2", "G3", "G4", "G5", "GR", "COLLISION"};
uint8_t gear_ind = 0;

void get_speed() 
{
    
    uint16_t speed_val = ((((uint32_t) read_adc(CHANNEL4))*100) / 1023); 
    char speed[8];
    sprintf(speed, "%u", speed_val); 
    int len = strlen(speed);
    can_transmit(SPEED_MSG_ID, (uint8_t *) speed, len);
    for (volatile uint16_t i = 0; i < 2000; i++);
}

void get_gear_pos() {
    
    char gear[5];
    unsigned char key = read_digital_keypad(STATE_CHANGE);
    if (key == SWITCH1 && gear_ind < 5) {
        gear_ind++;
        can_transmit(GEAR_MSG_ID, &gear_ind, 1);
        for (volatile uint16_t i = 0; i < 2000; i++);
        return;
    } else if (key == SWITCH2 && gear_ind > 0) {
        gear_ind--;
        can_transmit(GEAR_MSG_ID, &gear_ind, 1);
        for (volatile uint16_t i = 0; i < 2000; i++);
        return;

    } else if (key == SWITCH3) 
    {
        gear_ind = 6;
        char gear_rev = 'R';
        can_transmit(GEAR_MSG_ID, &gear_rev, 1);
        for (volatile uint16_t i = 0; i < 2000; i++);

        return;

    } else if (key == SWITCH4) 
    {
        gear_ind = 7;
        char gear_col = 'C';
        can_transmit(GEAR_MSG_ID, &gear_col, 1);
        for (volatile uint16_t i = 0; i < 2000; i++);

        return;

    }
    can_transmit(GEAR_MSG_ID, &gear_ind, 1);
    for (volatile uint16_t i = 0; i < 2000; i++);

}
