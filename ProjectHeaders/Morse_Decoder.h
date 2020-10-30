/* 
 * File:   Morse_Decoder.h
 * Author: chris
 *
 * Created on October 18, 2020, 12:32 AM
 */

#ifndef MORSE_DECODER_H
#define	MORSE_DECODER_H

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

//Service module functions
bool InitMorse_Decoder(uint8_t Priority);
bool PostMorse_Decoder(ES_Event_t ThisEvent);
ES_Event_t RunMorse_Decoder(ES_Event_t ThisEvent);

//module functions
char DecodeMorseString(void);

#endif	/* MORSE_DECODER_H */

