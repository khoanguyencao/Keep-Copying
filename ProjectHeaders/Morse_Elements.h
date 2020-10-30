/* 
 * File:   Morse_Elements.h
 * Author: chris
 *
 * Created on October 17, 2020, 6:19 AM
 */

#ifndef MORSE_ELEMENTS_H
#define	MORSE_ELEMENTS_H

#include <stdint.h>
#include <stdbool.h>
#include "S1_OLED_Write.h"
#include "ES_Events.h"
#include "ES_Port.h" 
#include "EventCheckers.h"

#include <xc.h>
#include <p32xxxx.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/attribs.h>
#include <sys/kmem.h>

//type def
typedef enum{
    INIT_MORSE_ELEM=0,
    CAL_WAIT_FOR_RISE,
    CAL_WAIT_FOR_FALL,
    EOC_WAIT_RISE,
    EOC_WAIT_FALL,
    DECODE_WAIT_RISE,
    DECODE_WAIT_FALL
}MState_t;

//Service module functions
bool InitMorse_Elem(uint8_t Priority);
bool PostMorse_Elem(ES_Event_t ThisEvent);
ES_Event_t RunMorse_Elem(ES_Event_t ThisEvent);

//module functions
void Calibration(void);

//Event Checking Functions
bool Check_Morse_Elem(void);
void C_Space(void);
void C_Pulse(void);


bool Check4Press(void);
#endif	/* MORSE_ELEMENTS_H */

