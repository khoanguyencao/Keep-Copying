// This module
#include "Morse_Elements.h"
#include "../ProjectHeaders/Morse_Decoder.h"
#include "S1_OLED_Write.h"
#include "../u8g2Headers/portmap.h"
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
#include "EventCheckers.h"

/*----------------------------- Module Defines ----------------------------*/


/*---------------------------- Module Variables ---------------------------*/
// with the introduction of Gen2, we need a module level Priority variable
static uint8_t MyPriority;
static MState_t Current_State;
static uint8_t LastInput_State;
static uint16_t First_Delta;
static uint16_t Time_LastRise;
static uint16_t Time_LastFall;
static uint16_t Length_Dot;

/*------------------------------ Module Code ------------------------------*/
/****************************************************************************
 Function
     InitMorseElem
 Parameters
     uint8_t : the priorty of this service
 Returns
     bool, false if error in initialization, true otherwise
 Description
     Initializes port to receive input, samples input, and set system variables
 *   LastInput_State, Current_State, and First Delta
 *   set current state to Send Char
****************************************************************************/
bool InitMorse_Elem(uint8_t Priority)
{
  ES_Event_t ThisEvent;

  MyPriority = Priority;
  
        //Set Pin RB4 to input for MORSE code
        pinMode(RB4, INPUT);
        pinMode(RB5, INPUT); // for now as event trigger
        //Last Input State Variable initialization by sampling RB4
        LastInput_State = digitalRead(RB4);

        //Setting Current State of State Machine
        Current_State = INIT_MORSE_ELEM;
        
        //Initializing first timing Delta for dot measurement
        First_Delta=0;     
        
        // post the initial transition event
        ThisEvent.EventType = ES_INIT;
  
          if (ES_PostToService(MyPriority, ThisEvent) == true)
          {
            return true;
          }
          else
          {
            return false;
          }
}

/****************************************************************************
 Function
     PostMorse_Elem
 Parameters
     EF_Event ThisEvent ,the event to post to the queue
 Returns
     bool false if the Enqueue operation failed, true otherwise
 Description
     Posts an event to this state machine's queue
****************************************************************************/
bool PostMorse_Elem(ES_Event_t ThisEvent)
{
  return ES_PostToService(MyPriority, ThisEvent);
}

/****************************************************************************
 Function
    RunMorse_Elem
 Parameters
   ES_Event : the event to process
 Returns
   ES_Event, ES_NO_EVENT if no error ES_ERROR otherwise
 Description
respond to rise and fall events, perform calibration to differentiate a pulse 
 * dot length from a dash length, char space length or word space length
 * post pulses and spaces to decoder state machine
 * If calibration is called, post to OLED to notify user of calibration
****************************************************************************/
ES_Event_t RunMorse_Elem(ES_Event_t ThisEvent)
{
  ES_Event_t ReturnEvent;
  ReturnEvent.EventType = ES_NO_EVENT; // assume no errors
  
/*-----------------------------------------------------------------------------
 * Current State switch case statement, Compares INIT_MORSE_ELEM,
 * CAL_WAIT_FOR_RISE, CAL_WAIT_FOR_FALL, EOC_WAIT_RISE, EOC_WAIT_FALL,
 * DECODE_WAIT_RISE, and DECODE_WAIT_FALL
 * Used to transition from calibration to the start of a valid morse char
 * --------------------------------------------------------------------------*/  
  switch (Current_State)
  {
    case INIT_MORSE_ELEM:
    {
        if (ThisEvent.EventType == ES_INIT)
        {
            //initialization 
            printf("set new current state CAL_WAIT_FOR_RISE \r\n");
            Current_State = CAL_WAIT_FOR_RISE; 
        }
    }
    break;
    
    case CAL_WAIT_FOR_RISE://waiting for a rise to document pulse length
    {
       printf("In current state CAL_WAIT_FOR_RISE \r\n"); 
       switch (ThisEvent.EventType)
       {
           case ES_RISING_EDGE:
           {
                //Received a rising edge event
                Time_LastRise = ThisEvent.EventParam;
                //printf("R with time %d \r\n", Time_LastRise);
                Current_State = CAL_WAIT_FOR_FALL;
           }
           break;
           case ES_CAL_COMPLETE://transition to determine start of char
           {
               Current_State = EOC_WAIT_RISE;
           }
           default:{}break;
       }
    }
    break;
    
    case CAL_WAIT_FOR_FALL://waiting for a fall to document pulse length
    {
       //printf("In current state CAL_WAIT_FOR_FALL \r\n"); 
        switch (ThisEvent.EventType)
       {
           case ES_FALLING_EDGE:
           {
                //Received a rising edge event
                Time_LastFall = ThisEvent.EventParam;
                //printf("F with time %d \r\n", Time_LastFall);
                Current_State = CAL_WAIT_FOR_RISE;
                Calibration();
           }
           break;
           
           default:{}break;
       }
    }
    break;
    
    case EOC_WAIT_RISE:
    {
       //printf("In current state EOC_WAIT_RISE \r\n"); 
        switch (ThisEvent.EventType)
       {
           case ES_RISING_EDGE:
           {
                //Received a rising edge event
                Time_LastRise = ThisEvent.EventParam;
                Current_State = EOC_WAIT_FALL;
                C_Space();
           }
           break;
           
           case ES_PRESS:
           {
                Current_State = CAL_WAIT_FOR_RISE;
           }
            break;
           
           default:{}break;
        }
    }
    break;

    case EOC_WAIT_FALL:
    {
       //printf("In current state EOC_WAIT_FALL \r\n"); 
        switch (ThisEvent.EventType)
       {
            case ES_FALLING_EDGE:
            {
                 //Received a rising edge event
                 Time_LastFall = ThisEvent.EventParam;
                 Current_State = EOC_WAIT_RISE;
            }
            break;
           
            case ES_EOC_DETECTED:
            {
                 Current_State = DECODE_WAIT_FALL;
            }
            break;
           
            case ES_EOW_DETECTED:
            {
                Current_State = DECODE_WAIT_FALL;
            }
            break;
            
           //if statement code for calibration goes here
           case ES_PRESS:
           {
                Current_State = CAL_WAIT_FOR_RISE;
           }
           
            default:{}break;
        }
    }
    break;
    
    case DECODE_WAIT_RISE:
    {
       //printf("In current state DECODE_WAIT_RISE \r\n"); 
       switch (ThisEvent.EventType)
       {
           case ES_RISING_EDGE:
           {
                //Received a rising edge event
                Time_LastRise = ThisEvent.EventParam;
                Current_State = DECODE_WAIT_FALL;
                C_Space();
           }
           break;
           // calibration goes here
           case ES_PRESS:
           {
                Current_State = CAL_WAIT_FOR_RISE;
           }
           
           default:{}break;
       }
    }
    break;
    
    case DECODE_WAIT_FALL://awaiting a fall to determine space length
    {
       //printf("In current state DECODE_WAIT_FALL \r\n"); 
       switch (ThisEvent.EventType)
       {
           case ES_FALLING_EDGE:
           {
                //Received a rising edge event
                Time_LastFall = ThisEvent.EventParam;
                Current_State = DECODE_WAIT_RISE;
                C_Pulse();//characterize space length
           }
           break;
           // calibration goes here
           case ES_PRESS:
           {
                Current_State = CAL_WAIT_FOR_RISE;
           }
           
           default:{}break;
       }
    }
    break;
    
    default:
    {}
     break;
  }

  return ReturnEvent;
}

/*----------------------------------------------------------------------------
 * Event Checker for Morse Input
 * Takes no parameters, returns true if event is posted,
 * checks for rise and falls of input to distinguish morse elements
 ---------------------------------------------------------------------------*/

bool Check_Morse_Elem(void)
{
    //Local variable initialization
    static uint8_t CurrentInput_State;
    bool ReturnVal = false;
    static ES_Event_t ThisEvent;
    
    //Sample input
    CurrentInput_State = digitalRead(RB4);
    
    /*-----------------------------------------------------------------------
     Compare Current State to last state, any differences indicate a
     Falling Edge (1 to 0) or a rising edge (0 to 1)
     post event to myself, passing time to calculate deltas and determine if a 
     dot, dash, char space, or word space was passed. Also used for calibration
     -----------------------------------------------------------------------*/
    if (CurrentInput_State != LastInput_State)
    {
        //Change value of last state to current state to determine next edge
        LastInput_State = CurrentInput_State;
        //Determine if rising or falling edge detected and post
        if (CurrentInput_State == 1)
        {
            ThisEvent.EventType = ES_RISING_EDGE;
            ThisEvent.EventParam = ES_Timer_GetTime();
            PostMorse_Elem(ThisEvent);
            //printf("R from event checker \r\n");
        }
        else
        {
            ThisEvent.EventType = ES_FALLING_EDGE;
            ThisEvent.EventParam = ES_Timer_GetTime();
            PostMorse_Elem(ThisEvent);
            //printf("F from event checker \r\n");
        }
        ReturnVal = true;
    }
    return ReturnVal;
}

/*----------------------------------------------------------------------------
 * Calibration test function
 * Takes no parameters, returns nothing
 * checks for rise and falls of input to measure dot time length
 ---------------------------------------------------------------------------*/
void Calibration(void)
{
    //Variable to compare with First Delta to obtain dot length
    static uint16_t Second_Delta;
    static ES_Event_t ThisEvent;
    
    if (First_Delta == 0)
    {
        //Setting First Delta to first pulse width
        First_Delta = Time_LastFall - Time_LastRise;
    }
    else
    {
        //Setting Second Delta to second Pulse Width
        Second_Delta = Time_LastFall - Time_LastRise;
        //Obtaining Length of Dot (1:3 dot dash relation)
        //Dot followed by dash
        if ((100.0 * First_Delta / Second_Delta) <= 33.33)
        {
            Length_Dot = First_Delta;
            ThisEvent.EventType = ES_CAL_COMPLETE;
            PostMorse_Elem(ThisEvent);
            printf("dot is %d \r\n", Length_Dot);
        }
        //Dash followed by dot
        else if ((100.0 * First_Delta / Second_Delta) >= 300.00)
        {
            Length_Dot = Second_Delta;
            ThisEvent.EventType = ES_CAL_COMPLETE;
            PostMorse_Elem(ThisEvent);
            printf("dot is %d \r\n", Length_Dot);
        }
        //any other relation that is not useful
        else
        {
            First_Delta = Second_Delta;
        }
    }
}

/*----------------------------------------------------------------------------
 * Characterize space function
 * Takes no parameters, returns nothing
 * checks for char space, word space, bad space
 ---------------------------------------------------------------------------*/
void C_Space(void)
{
    //Local variables for calculations and event posting
    static uint16_t Last_Interval;
    ES_Event_t ThisEvent;
    
    //delta between falling and rising edges (space length)
    Last_Interval = Time_LastRise - Time_LastFall; 
    //printf("space length %d \r\n", Last_Interval);
    //printf("dot length %d \r\n", Length_Dot);
    /*----------------------------------------------------------------------
     If the space does not corresponds to a dot length, then it must be 
     either a char space, word space, or a bad space (this one requires
     re-calibration)
     ------------------------------------------------------------------------*/
    if (Last_Interval != Length_Dot)
    {
        //Char Space 3*Dot Length +-1
        if ((Last_Interval >= (3*(Length_Dot-1))) && (Last_Interval <= (3*(Length_Dot+1))))
        {
            ThisEvent.EventType = ES_EOC_DETECTED;
            PostMorse_Elem(ThisEvent);
            PostMorse_Decoder(ThisEvent);
            printf("cs \r\n");
        }
        else
        {
            //Word Space 7*Dot Length +-1
            if ((Last_Interval >= (7*(Length_Dot-1))) && (Last_Interval <= (7*(Length_Dot+1))))
            {
                ThisEvent.EventType = ES_EOW_DETECTED;
                PostMorse_Elem(ThisEvent);
                PostMorse_Decoder(ThisEvent);
                printf("ws \r\n");
            }
            else if ((Last_Interval < ((Length_Dot-1))) && (Last_Interval > ((Length_Dot+1))))
            {
                //post bad space
                ThisEvent.EventType = ES_BAD_SPACE;
                printf("Bad SPace\r\n");
                //PostMorse_Decoder(ThisEvent);
            }
        }
    }
}
/*----------------------------------------------------------------------------
 * Characterize pulse function
 * Takes no parameters, returns nothing
 * checks for dot or dash
 ---------------------------------------------------------------------------*/
void C_Pulse(void)
{
    //Local variables for calculations and event posting
    static uint16_t Last_PulseWidth;
    static ES_Event_t ThisEvent;
    
    //delta between falling and rising edges (space length)
    Last_PulseWidth = Time_LastFall - Time_LastRise; 
    
    /*----------------------------------------------------------------------
     If the pulse does correspond to a dot length, then submit dot, if it 
     * corresponds to a dash submit dash, otherwise bad pulse
     ------------------------------------------------------------------------*/
    //Dot found
    if ((Last_PulseWidth >= (Length_Dot-1)) && (Last_PulseWidth <= (Length_Dot+1)))
    {
        ThisEvent.EventType = ES_DOT;
        PostMorse_Decoder(ThisEvent);
        printf(".");
    }
    else
    {
        //Dash Found
        if ((Last_PulseWidth >= (3*(Length_Dot-1))) && (Last_PulseWidth <= (3*(Length_Dot+1))))
        {
            ThisEvent.EventType = ES_DASH;
            PostMorse_Decoder(ThisEvent);
            printf("-");
        }
        //Bad Pulse (may require calibration)
        else if ((Last_PulseWidth < ((Length_Dot-1))) && (Last_PulseWidth > ((Length_Dot+1))))
        {
            //post bad pulse
            ThisEvent.EventType = ES_BAD_PULSE;
            PostMorse_Decoder(ThisEvent);
        }
    }
}