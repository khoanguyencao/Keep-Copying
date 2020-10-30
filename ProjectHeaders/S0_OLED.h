/* 
 * File:   S0_OLED.h
 * Author: chris
 *
 * Created on October 10, 2020, 10:31 PM
 */

#ifndef S0_OLED_H
#define	S0_OLED_H

#include <stdint.h>
#include <stdbool.h>
#include "S1_OLED_Write.h"
#include "ES_Events.h"
#include "ES_Port.h"                // needed for definition of REENTRANT


// Public Function Prototypes
bool InitS0_OLED(uint8_t Priority);
bool PostS0_OLED(ES_Event_t ThisEvent);
ES_Event_t RunS0_OLED(ES_Event_t ThisEvent);

#endif	/* S0_OLED_H */

