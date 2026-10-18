#include "ecu2_sensor.h"
#include "adc.h"
#include "can.h"
#include "msg_id.h"
#include "uart.h"
#include <stdio.h>
void init_config()
{
    init_can();
    init_adc();
    init_digital_keypad();
    
}

int main()
{
    //call the functions
    init_config();
    TRISB = 0x08;    // RB3 = CAN RX must stay input

    PORTB = 0x00;
    char str[100];
    while(1)
    {
        get_rpm(); //all the data will be transimtted inside the functions itself 
        process_indicator(); 
    }

}
