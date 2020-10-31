/****************************************************************************
 Module
   TestHarnessService0.c

 Revision
   1.0.1

 Description
   This is the first service for the Test Harness under the
   Gen2 Events and Services Framework.

 Notes

 History
 When           Who     What/Why
 -------------- ---     --------
 10/26/17 18:26 jec     moves definition of ALL_BITS to ES_Port.h
 10/19/17 21:28 jec     meaningless change to test updating
 10/19/17 18:42 jec     removed referennces to driverlib and programmed the
                        ports directly
 08/21/17 21:44 jec     modified LED blink routine to only modify bit 3 so that
                        I can test the new new framework debugging lines on PF1-2
 08/16/17 14:13 jec      corrected ONE_SEC constant to match Tiva tick rate
 11/02/13 17:21 jec      added exercise of the event deferral/recall module
 08/05/13 20:33 jec      converted to test harness service
 01/16/12 09:58 jec      began conversion from TemplateFSM.c
****************************************************************************/
/*----------------------------- Include Files -----------------------------*/
// This module
#include "../ProjectHeaders/TestHarnessService0.h"
#include "../ProjectHeaders/Seq.h"
// debugging printf()
//#include "dbprintf.h"

// Hardware
#include <xc.h>
#include <proc/p32mx170f256b.h>
#include <sys/attribs.h> // for ISR macors
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Event & Services Framework
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "ES_DeferRecall.h"
#include "ES_ShortTimer.h"
#include "ES_Port.h"

// My Modules
#include "Seq.h"
#include "Display.h"
#include "Dotstar.h"

/*----------------------------- Module Defines ----------------------------*/
/*---------------------------- Module Functions ---------------------------*/
/* prototypes for private functions for this service.They should be functions
   relevant to the behavior of this service
*/
/*---------------------------- Module Variables ---------------------------*/
// with the introduction of Gen2, we need a module level Priority variable
static uint8_t MyPriority;
// add a deferral queue for up to 3 pending deferrals +1 to allow for overhead
static ES_Event_t DeferralQueue[3 + 1];


 
/*------------------------------ Module Code ------------------------------*/
/****************************************************************************
 Function
     InitTestHarnessService0

 Parameters
     uint8_t : the priorty of this service

 Returns
     bool, false if error in initialization, true otherwise

 Description
     Saves away the priority, and does any
     other required initialization for this service
 Notes

 Author
     J. Edward Carryer, 01/16/12, 10:00
****************************************************************************/
bool InitTestHarnessService0(uint8_t Priority)
{
  ES_Event_t ThisEvent;

  MyPriority = Priority;
  /********************************************
   in here you write your initialization code
   *******************************************/
  // initialize deferral queue for testing Deferal function
  ES_InitDeferralQueueWith(DeferralQueue, ARRAY_SIZE(DeferralQueue));
  // initialize LED drive for testing/debug output

  // initialize the Short timer system for channel A
  //ES_ShortTimerInit(MyPriority, SHORT_TIMER_UNUSED);
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
     PostTestHarnessService0

 Parameters
     EF_Event ThisEvent ,the event to post to the queue

 Returns
     bool false if the Enqueue operation failed, true otherwise

 Description
     Posts an event to this state machine's queue
 Notes

 Author
     J. Edward Carryer, 10/23/11, 19:25
****************************************************************************/
bool PostTestHarnessService0(ES_Event_t ThisEvent)
{
  return ES_PostToService(MyPriority, ThisEvent);
}

/****************************************************************************
 Function
    RunTestHarnessService0

 Parameters
   ES_Event : the event to process

 Returns
   ES_Event, ES_NO_EVENT if no error ES_ERROR otherwise

 Description
   add your description here
 Notes

 Author
   J. Edward Carryer, 01/15/12, 15:23
****************************************************************************/
ES_Event_t RunTestHarnessService0(ES_Event_t ThisEvent)
{
  ES_Event_t ReturnEvent;
  ReturnEvent.EventType = ES_NO_EVENT; // assume no errors
  static char DeferredChar = '1';

#ifdef _INCLUDE_BYTE_DEBUG_
  _HW_ByteDebug_SetValueWithStrobe( ENTER_RUN );
#endif  

  switch (ThisEvent.EventType)
  {
    case ES_INIT:
    {
        printf("key shifter \r\n");
    }
    break;
    case ES_TIMEOUT:
    {
       printf("timeout param %d \r\n", ThisEvent.EventParam);
    }
    break;
    case ES_NEW_KEY:   // announce
    {
      printf("ES_NEW_KEY received with -> %c <- in Service 0\r\n",
          (char)ThisEvent.EventParam);
      if ('q' == ThisEvent.EventParam)
      {
          printf("key %c \r\n",ThisEvent.EventParam);
          printf("%d\n", rand() % 8);

      }
      if ('a' == ThisEvent.EventParam)
      {
        printf("key %c \r\n",ThisEvent.EventParam);
        ES_Timer_InitTimer(TEST_TIMER, 5000);
      }
      if ('z' == ThisEvent.EventParam)
      {
          ThisEvent.EventType = ES_FIRST_ROUND;
          PostSequence(ThisEvent);
      }
      if ('x' == ThisEvent.EventParam)
      {
          ThisEvent.EventType = ES_NEXT_ROUND;
          PostSequence(ThisEvent);
      }
      if ('c' == ThisEvent.EventParam)
      {
          ThisEvent.EventType = ES_TIMEOUT;
          PostSequence(ThisEvent);
      }
      if ('v' == ThisEvent.EventParam)
      {
          ThisEvent.EventType = ES_TIMEOUT;
          ThisEvent.EventParam = 10;
          PostSequence(ThisEvent);
      }
      if ('b' == ThisEvent.EventParam)
      {
          ThisEvent.EventType = ES_INCORRECT_INPUT;
          PostSequence(ThisEvent);
      }
      if ('n' == ThisEvent.EventParam)
      {
          ThisEvent.EventType = ES_CORRECT_INPUT;
          PostSequence(ThisEvent);
      }
      if ('m' == ThisEvent.EventParam)
      {
          ThisEvent.EventType = ES_CORRECT_INPUT_FINAL;
          ThisEvent.EventParam = 10;
          PostSequence(ThisEvent);
      }
      
      if ('w' == ThisEvent.EventParam)
      {
          ThisEvent.EventType = ES_DISPLAY_WELCOME;
          PostDisplay(ThisEvent);
      }
      
      if ('e' == ThisEvent.EventParam)
      {
          ThisEvent.EventType = ES_DISPLAY_READY;
          PostDisplay(ThisEvent);
      }
      
      if ('r' == ThisEvent.EventParam)
      {
          ThisEvent.EventType = ES_DISPLAY_PLAY_UPDATE;
          PostDisplay(ThisEvent);
      }
      
      if ('0' == ThisEvent.EventParam)
      {
          ThisEvent.EventType = ES_DISPLAY_INSTRUCTION;
          ThisEvent.EventParam = 0; //sets instruction
          PostDisplay(ThisEvent);
      }
      
      if ('1' == ThisEvent.EventParam)
      {
          ThisEvent.EventType = ES_DISPLAY_INSTRUCTION;
          ThisEvent.EventParam = 1; //sets instruction
          PostDisplay(ThisEvent);
      }
      
      if ('2' == ThisEvent.EventParam)
      {
          ThisEvent.EventType = ES_DISPLAY_INSTRUCTION;
          ThisEvent.EventParam = 2; //sets instruction
          PostDisplay(ThisEvent);
      }
      
      if ('3' == ThisEvent.EventParam)
      {
          ThisEvent.EventType = ES_DISPLAY_INSTRUCTION;
          ThisEvent.EventParam = 3; //sets instruction
          PostDisplay(ThisEvent);
      }
      
      if ('4' == ThisEvent.EventParam)
      {
          ThisEvent.EventType = ES_DISPLAY_INSTRUCTION;
          ThisEvent.EventParam = 4; //sets instruction
          PostDisplay(ThisEvent);
      }
      
      if ('5' == ThisEvent.EventParam)
      {
          ThisEvent.EventType = ES_DISPLAY_INSTRUCTION;
          ThisEvent.EventParam = 5; //sets instruction
          PostDisplay(ThisEvent);
      }
      
      if ('6' == ThisEvent.EventParam)
      {
          ThisEvent.EventType = ES_DISPLAY_PLAY_UPDATE;
          ThisEvent.EventParam = 6; //sets instruction
          PostDisplay(ThisEvent);
      }
      
      if ('7' == ThisEvent.EventParam)
      {
          ThisEvent.EventType = ES_DISPLAY_INSTRUCTION;
          ThisEvent.EventParam = 7; //sets instruction
          PostDisplay(ThisEvent);
      }
      
      if ('t' == ThisEvent.EventParam)
      {
          ThisEvent.EventType = ES_DISPLAY_GO;
          PostDisplay(ThisEvent);
      }
      
      if ('y' == ThisEvent.EventParam)
      {
          ThisEvent.EventType = ES_DISPLAY_ROUNDCOMPLETE;
          PostDisplay(ThisEvent);
      }
      
      if ('u' == ThisEvent.EventParam)
      {
          ThisEvent.EventType = ES_DISPLAY_GAMECOMPLETE;
          ThisEvent.EventParam = 9800;
          PostDisplay(ThisEvent);
      }
      
      if ('d' == ThisEvent.EventParam)
      {
          ThisEvent.EventType = ES_OFF;
          PostDotstar(ThisEvent);
      }
      
      if ('f' == ThisEvent.EventParam)
      {
          ThisEvent.EventType = ES_RED;
          PostDotstar(ThisEvent);
      }
      
      if ('g' == ThisEvent.EventParam)
      {
          ThisEvent.EventType = ES_GREEN;
          PostDotstar(ThisEvent);
      }
      
      if ('h' == ThisEvent.EventParam)
      {
          ThisEvent.EventType = ES_RANDOM;
          PostDotstar(ThisEvent);
      }
        
    }
    break;
    
    default:
    {}
     break;
  }

  return ReturnEvent;
}