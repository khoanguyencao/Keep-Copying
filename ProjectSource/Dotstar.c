/****************************************************************************
 Module
   Dotstar.c

 Revision
   1.0.1

 Description
    This is a state machine that creates the different flashing patterns for the
    Dotstar

 Notes

 History
 When           Who     What/Why
 -------------- ---     --------
 10/30/20 01:46 acg      first pass
 10/31/20 02:43 acg      restructured RunDotstar
****************************************************************************/
/*----------------------------- Include Files -----------------------------*/
/* include header files for this state machine as well as any machines at the
   next lower level in the hierarchy that are sub-machines to this machine
*/
// Hardware
#include <xc.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <proc/p32mx170f256b.h>
#include <sys/attribs.h> // for ISR macros

// Event & Services Framework
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "ES_DeferRecall.h"
#include "ES_ShortTimer.h"
#include "ES_Port.h"
#include "EventCheckers.h"

// My Modules
#include "Dotstar.h"
#include "GameState.h"
#include "spi_master.h"

/*----------------------------- Module Defines ----------------------------*/
// these times assume a 10.000mS/tick timing
#define ONE_SEC 1000
#define QUARTER_SEC (ONE_SEC / 4)
/*---------------------------- Module Functions ---------------------------*/
/* prototypes for private functions for this machine.They should be functions
   relevant to the behavior of this state machine
*/
void dotStar_Write(uint8_t Bright1, uint8_t Red1, uint8_t Blue1, uint8_t Green1, 
            uint8_t Bright2, uint8_t Red2, uint8_t Blue2, uint8_t Green2);

/*---------------------------- Module Variables ---------------------------*/
// everybody needs a state variable, you may need others as well.
// type of state variable should match that of enum in header file
static DotstarState_t CurrentState;

// with the introduction of Gen2, we need a module level Priority var as well
static uint8_t MyPriority;


/*------------------------------ Module Code ------------------------------*/
/****************************************************************************
 Function
     InitDotstar

 Parameters
     uint8_t : the priority of this service

 Returns
     bool, false if error in initialization, true otherwise

 Description
     Saves away the priority, sets up the initial transition and does any
     other required initialization for this state machine
 Notes

 Author
    A. Gin
****************************************************************************/
bool InitDotstar(uint8_t Priority)
{
  ES_Event_t ThisEvent;

  MyPriority = Priority;
  // put us into the Initial PseudoState
  CurrentState = DotstarInitPState;
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
     PostDotstar

 Parameters
     ES_Event_t ThisEvent , the event to post to the queue

 Returns
     boolean False if the Enqueue operation failed, True otherwise

 Description
     Posts an event to this state machine's queue
 Notes

 Author
    A. Gin
****************************************************************************/
bool PostDotstar(ES_Event_t ThisEvent)
{
  return ES_PostToService(MyPriority, ThisEvent);
}

/****************************************************************************
 Function
    RunDotstar

 Parameters
   ES_Event_t : the event to process

 Returns
   ES_Event_t, ES_NO_EVENT if no error ES_ERROR otherwise

 Description
   add your description here
 Notes
   uses nested switch/case to implement the machine.
 Author
   A. Gin
****************************************************************************/
ES_Event_t RunDotstar(ES_Event_t ThisEvent)
{
  static uint16_t flipflop;
  uint8_t red1, green1, blue1, red2, green2, blue2;
  ES_Event_t ReturnEvent;
  ReturnEvent.EventType = ES_NO_EVENT; // assume no errors

  switch (CurrentState)
  {
    /*--------------------------------------------------- DotstarInitPState*/      
    case DotstarInitPState:        
    {
        if (ThisEvent.EventType == ES_INIT)
        {
            //initialize SPI for dotstar
            SPI_Init_Dotstar();
            //transition to next case
            CurrentState = DotstarOff;
            // turn off LEDs
            dotStar_Write(0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00);
        }
    }
    break;
    
    /*---------------------------------------------------------- DotstarRed*/      
    case DotstarRed:        
    {
        if ((ThisEvent.EventType == ES_TIMEOUT) && (ThisEvent.EventParam == DOTSTAR_TIMER))
        {
            // increment flipflop
            flipflop = flipflop + 1;
            // if flipflop reaches 256, reset to 0
            if (flipflop > 255)
            {
                flipflop = 0;
            }
            
            if (flipflop%2 == 0)    // if flipflop is divisible by 2
            {
                // write LED1 red
                dotStar_Write(0xFF, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00);
                // set Dotstar timer
                ES_Timer_InitTimer(DOTSTAR_TIMER, QUARTER_SEC);
            }
            else                    // else flipflop is not divisible by 2
            {
                // write LED2 red
                dotStar_Write(0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00);
                // set Dotstar timer
                ES_Timer_InitTimer(DOTSTAR_TIMER, QUARTER_SEC);
            }
        }
        
        if (ThisEvent.EventType == ES_OFF)
        {
            // transition to DotstarOff state
            CurrentState = DotstarOff;
            // turn off LEDs
            dotStar_Write(0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00);
        }
        
        if (ThisEvent.EventType == ES_GREEN)
        {
            // transition to DotstarGreen state
            CurrentState = DotstarGreen;
            // set flipflop to 0
            flipflop = 0;
            // set Dotstar Timer
            ES_Timer_InitTimer(DOTSTAR_TIMER, QUARTER_SEC);
        }
        
        if (ThisEvent.EventType == ES_RANDOM)
        {
            // transition to DotstarRandom state
            CurrentState = DotstarRandom;
            // set flipflop to 0
            flipflop = 0;
            // set Dotstar Timer
            ES_Timer_InitTimer(DOTSTAR_TIMER, QUARTER_SEC);
        }
    }
    break;
    
    /*-------------------------------------------------------- DotstarGreen*/      
    case DotstarGreen:
    {        
        if ((ThisEvent.EventType == ES_TIMEOUT) && (ThisEvent.EventParam == DOTSTAR_TIMER))
        {
            // increment flipflop
            flipflop = flipflop + 1;
            // if flipflop reaches 256, reset to 0
            if (flipflop > 255)
            {
                flipflop = 0;
            }
            
            if (flipflop%2 == 0)    // if flipflop is divisible by 2
            {
                // write LED1 green
                dotStar_Write(0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00);
                // set Dotstar timer
                ES_Timer_InitTimer(DOTSTAR_TIMER, QUARTER_SEC);
            }
            else                    // else flipflop is not divisible by 2
            {
                // write LED2 green
                dotStar_Write(0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF);
                // set Dotstar timer
                ES_Timer_InitTimer(DOTSTAR_TIMER, QUARTER_SEC);
            }
        }
        
        if (ThisEvent.EventType == ES_OFF)
        {
            // transition to DotstarOff state
            CurrentState = DotstarOff;
            // turn off LEDs
            dotStar_Write(0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00);
        }
        
        if (ThisEvent.EventType == ES_RED)
        {
            // transition to DotstarRed state
            CurrentState = DotstarRed;
            // set flipflop to 0
            flipflop = 0;
            // set Dotstar Timer
            ES_Timer_InitTimer(DOTSTAR_TIMER, QUARTER_SEC);
        }
        
        if (ThisEvent.EventType == ES_RANDOM)
        {
            // transition to DotstarRandom state
            CurrentState = DotstarRandom;
            // set flipflop to 0
            flipflop = 0;
            // set Dotstar Timer
            ES_Timer_InitTimer(DOTSTAR_TIMER, QUARTER_SEC);
        }
    }
    break;
    
    /*------------------------------------------------------- DotstarRandom*/ 
    case DotstarRandom:
    {        
        if ((ThisEvent.EventType == ES_TIMEOUT) && (ThisEvent.EventParam == DOTSTAR_TIMER))
        {
            // increment flipflop
            flipflop = flipflop + 1;
            // if flipflop reaches 256, reset to 0
            if (flipflop > 255)
            {
                flipflop = 0;
            }
            
            if (flipflop%2 == 0)    // if flipflop is divisible by 2
            {
                // generate random color values
                red1 = rand();      // LED1
                blue1 = rand();
                green1 = rand();
                red2 = rand();      // LED2
                blue2 = rand();
                green2 = rand();
                // write LED1 and LED2 random colors
                dotStar_Write(0xFF, red1, green1, blue1, 0xFF, red2, green2, blue2);
                // set Dotstar timer
                ES_Timer_InitTimer(DOTSTAR_TIMER, QUARTER_SEC);
            }
            else                    // else flipflop is not divisible by 2
            {
                // generate random color values
                red1 = rand();      // LED1
                blue1 = rand();
                green1 = rand();
                red2 = rand();      // LED2
                blue2 = rand();
                green2 = rand();
                // write LED1 and LED2 random colors
                dotStar_Write(0xFF, red1, green1, blue1, 0xFF, red2, green2, blue2);
                // set Dotstar timer
                ES_Timer_InitTimer(DOTSTAR_TIMER, QUARTER_SEC);
            }
        }
        
        if (ThisEvent.EventType == ES_OFF)
        {
            // transition to DotstarOff state
            CurrentState = DotstarOff;
            // turn off LEDs
            dotStar_Write(0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00);
        }
        
        if (ThisEvent.EventType == ES_RED)
        {
            // transition to DotstarRed state
            CurrentState = DotstarRed;
            // set flipflop to 0
            flipflop = 0;
            // set Dotstar Timer
            ES_Timer_InitTimer(DOTSTAR_TIMER, QUARTER_SEC);
        }
        
        if (ThisEvent.EventType == ES_GREEN)
        {
            // transition to DotstarGreen state
            CurrentState = DotstarGreen;
            // set flipflop to 0
            flipflop = 0;
            // set Dotstar Timer
            ES_Timer_InitTimer(DOTSTAR_TIMER, QUARTER_SEC);
        }
    }
    break;
    
    /*---------------------------------------------------------- DotstarOff*/ 
    case DotstarOff:
    {        
        if (ThisEvent.EventType == ES_RED)
        {
            // transition to DotstarRed state
            CurrentState = DotstarRed;
            // set flipflop to 0
            flipflop = 0;
            // set Dotstar Timer
            ES_Timer_InitTimer(DOTSTAR_TIMER, QUARTER_SEC);
        }
        
        if (ThisEvent.EventType == ES_GREEN)
        {
            // transition to DotstarGreen state
            CurrentState = DotstarGreen;
            // set flipflop to 0
            flipflop = 0;
            // set Dotstar Timer
            ES_Timer_InitTimer(DOTSTAR_TIMER, QUARTER_SEC);
        }
        
        if (ThisEvent.EventType == ES_RANDOM)
        {
            // transition to DotstarRandom state
            CurrentState = DotstarRandom;
            // set flipflop to 0
            flipflop = 0;
            // set Dotstar Timer
            ES_Timer_InitTimer(DOTSTAR_TIMER, QUARTER_SEC);
        }
    }
    break;
    
    default:
      ;
  } 
  return ReturnEvent;
}

/****************************************************************************
 Function
     QueryDotstar

 Parameters
     None

 Returns
     DotstarState_t The current state of the Template state machine

 Description
     returns the current state of the Display state machine
 Notes

 Author
    A. Gin
****************************************************************************/
DotstarState_t QueryDotstar(void)
{
    return CurrentState;
}

/***************************************************************************
 private functions
 ***************************************************************************/

void dotStar_Write(uint8_t Bright1, uint8_t Red1, uint8_t Blue1, uint8_t Green1, 
            uint8_t Bright2, uint8_t Red2, uint8_t Blue2, uint8_t Green2){
    uint32_t data;
    //write start frame
    SPI_Write(0);
    
    //write first LED
    data = ((Bright1 << 24) | (Blue1 << 16) | (Green1 << 8) | (Red1));
    SPI_Write(data);
    
    //write second LED
    data = ((Bright2 << 24) | (Blue2 << 16) | (Green2 << 8) | (Red2));
    SPI_Write(data);
    
    //write reset frame
    SPI_Write(0);
    
    //write end frame
    SPI_Write(0);
}