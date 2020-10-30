#include "Morse_Elements.h"
#include "../ProjectHeaders/Morse_Decoder.h"
#include "../u8g2Headers/portmap.h"
#include "Morse_Elements.h"
#include "Morse_Decoder.h"
#include "S1_OLED_Write.h"
// Hardware
#include <xc.h>
#include <proc/p32mx170f256b.h>
#include <sys/attribs.h> // for ISR macors
#include <stdlib.h>
#include <string.h>
#include <proc/p32mx170f256b.h>
#include <sys/attribs.h> // for ISR macors

// Event & Services Framework
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "ES_DeferRecall.h"
#include "ES_ShortTimer.h"
#include "ES_Port.h"
#include "ES_Timers.h"

#if 0
//Variable for comparing states
static uint8_t Last_State = 0;

void Init_TB (void)
{
    pinMode(RA4, INPUT);
    Last_State = digitalRead(RA4);
    printf("RA4 state %d", Last_State);
}

//Event Checking function
//Must limit the amount of checking to not disrupt
//morse code decoding
bool Check4Press(void)
{
    static uint8_t Current_State;
    static ES_Event_t ThisEvent;
    Current_State = digitalRead(RA4);
    printf("RA4 state %d", Current_State);
    if (Current_State == 1)
    {
        if (Current_State != Last_State)
        {
            Last_State = 1;
            return false;
        }
    }
    else
    {
        if (Last_State ==1)
        {
            Last_State = 0;
            ThisEvent.EventType = ES_PRESS;
            PostMorse_Decoder(ThisEvent);
            PostMorse_Elem(ThisEvent);
            PostS1_OLED_Write(ThisEvent);
            return true;
        }
    }
    return false;
}

#endif


