// This module
#include "../ProjectHeaders/S0_OLED.h"
#include "../ProjectHeaders/S1_OLED_Write.h"
// Hardware
#include <xc.h>
#include <proc/p32mx170f256b.h>
#include <sys/attribs.h> // for ISR macors

// Event & Services Framework
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "ES_DeferRecall.h"
#include "ES_ShortTimer.h"
#include "ES_Port.h"

#include "../u8g2Headers/u8g2TestHarness_main.h"
#include "../u8g2Headers/common.h"
#include "../u8g2Headers/spi_master.h"
#include "../u8g2Headers/u8g2.h"
#include "../u8g2Headers/u8x8.h"

/*----------------------------- Module Defines ----------------------------*/
// these times assume a 10.000mS/tick timing
#define ONE_SEC 1000
#define HALF_SEC (ONE_SEC / 2)
#define QUARTER_SEC (ONE_SEC / 4)

/*---------------------------- Module Variables ---------------------------*/
// with the introduction of Gen2, we need a module level Priority variable
static uint8_t MyPriority;
static State_t Current_State;
/*------------------------------ Module Code ------------------------------*/
/****************************************************************************
 Function
    InitS0_OLED
 Parameters
     uint8_t : the priorty of this service
 Returns
     bool, false if error in initialization, true otherwise
 Description
     Initializes by sending event to Service 1 to write first character and 
 *   set current state to Send Char
****************************************************************************/
bool InitS0_OLED(uint8_t Priority)
{
  ES_Event_t ThisEvent;

  MyPriority = Priority;

  // post the initial transition event
  Current_State = PS_INIT;
  ThisEvent.EventType = ES_PS_INIT;
  
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
     PostS0_OLED
 Parameters
     EF_Event ThisEvent ,the event to post to the queue
 Returns
     bool false if the Enqueue operation failed, true otherwise
 Description
     Posts an event to this state machine's queue
****************************************************************************/
bool PostS0_OLED(ES_Event_t ThisEvent)
{
  return ES_PostToService(MyPriority, ThisEvent);
}

/****************************************************************************
 Function
    RunS0_OLED
 Parameters
   ES_Event : the event to process
 Returns
   ES_Event, ES_NO_EVENT if no error ES_ERROR otherwise
 Description
 Inserts a 1 sec delay or send event to service 1 upon timer end to write
 * to OLED
****************************************************************************/
ES_Event_t RunS0_OLED(ES_Event_t ThisEvent)
{
  ES_Event_t ReturnEvent;
  ReturnEvent.EventType = ES_NO_EVENT; // assume no errors

/*-----------------------------------------------------------------------------
 * Current State switch case statement, Compares PS_INIT, and SEND_CHAR
 * --------------------------------------------------------------------------*/  
  switch (Current_State)
  {
    case PS_INIT:
    {
        if (ThisEvent.EventType == ES_PS_INIT)
        {
            ES_Timer_InitTimer(SERVICE0_TIMER, 250);//Initialize timer
            ThisEvent.EventType = ES_WRITE;//Write event to send to OLED Write
            PostS1_OLED_Write(ThisEvent);//Post event to OLED Write
            Current_State = SEND_CHAR;//Set state
        }
    }
    break;
    case SEND_CHAR:   
    {
        /*--------------------------------------------------------------------
         * If timeout received, restart timer and post write event to OLED Write
         * ------------------------------------------------------------------*/  
        if(ThisEvent.EventType == ES_TIMEOUT)
        {
            ES_Timer_InitTimer(SERVICE0_TIMER, 250);
            ThisEvent.EventType = ES_WRITE;
            PostS1_OLED_Write(ThisEvent); 
            printf("I posted to S1 \r\n");
        }
    }
    break;
    default:
    {}
     break;
  }

  return ReturnEvent;
}




