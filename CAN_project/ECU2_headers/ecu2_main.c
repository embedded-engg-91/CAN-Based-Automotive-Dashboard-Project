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
    
    init_config();
    TRISB = 0x08;    

    PORTB = 0x00;
    char str[100];
    while(1)
    {
        get_rpm(); 
        process_indicator(); 
    }

}
