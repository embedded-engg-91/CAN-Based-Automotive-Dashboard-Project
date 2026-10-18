#include "ecu2_sensor.h"
#include "adc.h"
#include "can.h"
#include "msg_id.h"
#include "uart.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>

volatile IndicatorStatus prev_ind_status = e_ind_off;
volatile IndicatorStatus cur_ind_status = e_ind_off;
volatile unsigned char led_state = LED_OFF;

void get_rpm() {
    
    char rpm[8];
    uint16_t rpm_val = ((((uint32_t) read_adc(CHANNEL4))*6000) / 1023);
    sprintf(rpm, "%u", rpm_val);
    int len = strlen(rpm);
    can_transmit(RPM_MSG_ID, (uint8_t*) rpm, (uint8_t) len);
    for (uint16_t i = 0; i < 5000; i++);
}

uint16_t get_engine_temp() {
    
    char temp[8];
    uint16_t m_vtg = ((((uint32_t) read_adc(CHANNEL6))) / 1023) * 0.00488; 
    uint16_t temp_val = m_vtg / (10 * 1000);
    sprintf(temp, "%u", temp_val);
    int len = strlen(temp);
    can_transmit(ENG_TEMP_MSG_ID, (uint8_t*) temp, (uint8_t) len);
    for (uint16_t i = 0; i < 5000; i++);

}

void process_indicator() {
    
    unsigned char key = read_digital_keypad(STATE_CHANGE);
    char indicator[3];
    if (key == SWITCH1) {

        if (cur_ind_status == e_ind_left) {
            cur_ind_status = e_ind_off;
            LEFT_IND_OFF();
        } else 
        {
            cur_ind_status = e_ind_left;
            RIGHT_IND_OFF();
            LEFT_IND_ON();
        }
    } else if (key == SWITCH2) {
        if (cur_ind_status == e_ind_right) {
            cur_ind_status = e_ind_off;
            RIGHT_IND_OFF();
        } else 
        {
            cur_ind_status = e_ind_right;
            LEFT_IND_OFF();
            RIGHT_IND_ON();
        }
    } else if (key == SWITCH3) {
        if (cur_ind_status == e_ind_headlight) {
            cur_ind_status = e_ind_off;
            MIDDLE_FOUR_OFF();
        } else 
        {
            cur_ind_status = e_ind_headlight;
            MIDDLE_FOUR_ON();
        }
    } else if (key == SWITCH4) {
        if (cur_ind_status == e_ind_hazard) {
            cur_ind_status = e_ind_off;
            LEFT_IND_OFF();
            RIGHT_IND_OFF();
            MIDDLE_FOUR_OFF();
        } else 
        {
            cur_ind_status = e_ind_hazard;
            LEFT_IND_ON();
            RIGHT_IND_ON();
            MIDDLE_FOUR_ON();
        }
    }
    uint8_t tx_status = (uint8_t) cur_ind_status; 
    can_transmit(INDICATOR_MSG_ID, &tx_status, 1);
    for (uint16_t i = 0; i < 5000; i++);

}
