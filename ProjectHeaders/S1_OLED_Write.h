/* 
 * File:   S1_OLED_Write.h
 * Author: chris
 *
 * Created on October 10, 2020, 8:45 PM
 */

#ifndef S1_OLED_WRITE_H
#define	S1_OLED_WRITE_H

#include <stdint.h>
#include <stdbool.h>

#include "ES_Events.h"
#include "ES_Port.h"                // needed for definition of REENTRANT

//hardware
#include "../u8g2Headers/common.h"
#include "../u8g2Headers/spi_master.h"
#include "../u8g2Headers/u8g2.h"
#include "../u8g2Headers/u8x8.h"

#include <xc.h>
#include <p32xxxx.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/attribs.h>
#include <sys/kmem.h>

#define _XTAL_FREQ 40000000UL

#define SS_TRIS     TRISBbits.TRISB2
#define SS_PIN      LATBbits.LATB2
#define DC_TRIS     TRISBbits.TRISB13
#define DC_PIN      LATBbits.LATB13
#define RST_TRIS    TRISBbits.TRISB12
#define RST_PIN     LATBbits.LATB12

//type def
typedef enum{
    PS_INIT=0,
    NOT_BUSY,
    WRITING,
    SEND_CHAR
}State_t;

// Public Function Prototypes
bool InitS1_OLED_Write(uint8_t Priority);
bool PostS1_OLED_Write(ES_Event_t ThisEvent);
ES_Event_t RunS1_OLED_Write(ES_Event_t ThisEvent);

//Event CHecking Function
bool NextPage(void);

//Line manipulation function
void lineBufferENH(const char *str);
#endif	/* S1_OLED_WRITE_H */

