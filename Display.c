/****************************************************************************
 Module
   Display.c

 Revision
   1.0.1

 Description
    This is a state machine that creates the different screens for the game and 
    writes them to the OLED display.

 Notes

 History
 When           Who     What/Why
 -------------- ---     --------
 10/28/20 07:59 acg      first pass
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
#include "Display.h"
#include "ES_DeferRecall.h"
#include "ES_ShortTimer.h"
#include "ES_Port.h"
#include "EventCheckers.h"

// OLED
#include "../u8g2Headers/common.h"
#include "../u8g2Headers/spi_master.h"
#include "../u8g2Headers/u8g2.h"
#include "../u8g2Headers/u8x8.h"

/*----------------------------- Module Defines ----------------------------*/

/*---------------------------- Module Functions ---------------------------*/
/* prototypes for private functions for this machine.They should be functions
   relevant to the behavior of this state machine
*/

/*---------------------------- Module Variables ---------------------------*/
// everybody needs a state variable, you may need others as well.
// type of state variable should match that of enum in header file
static DisplayState_t CurrentState;
static uint8_t LastDisplayState;

// keep track of values needing to be written on the display
static uint16_t score = 1234;
static uint16_t time = 15;
static uint16_t input;
static uint16_t round = 1;
static uint16_t instruction;

// with the introduction of Gen2, we need a module level Priority var as well
static uint8_t MyPriority;

// OLED variables
extern uint8_t u8x8_pic32_gpio_and_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
extern uint8_t u8x8_byte_pic32_hw_spi(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
static u8g2_t u8g2;

// add a deferral queue for up to 2 pending deferrals to allow for overhead
static ES_Event_t DeferralQueue[2];
/*------------------------------ Module Code ------------------------------*/
/****************************************************************************
 Function
     InitDisplay

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
bool InitDisplay(uint8_t Priority)
{
  ES_Event_t ThisEvent;

  MyPriority = Priority;
  //initialize deferral queue
  ES_InitDeferralQueueWith(DeferralQueue, ARRAY_SIZE(DeferralQueue));
  // put us into the Initial PseudoState
  CurrentState = DisplayInitPState;
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
     PostDisplay

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
bool PostDisplay(ES_Event_t ThisEvent)
{
  return ES_PostToService(MyPriority, ThisEvent);
}

/****************************************************************************
 Function
    RunDisplay

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
ES_Event_t RunDisplay(ES_Event_t ThisEvent)
{
  ES_Event_t ReturnEvent;
  ReturnEvent.EventType = ES_NO_EVENT; // assume no errors

  switch (CurrentState)
  {
    /*---------------------------------------------------------- InitPState*/   
    case DisplayInitPState:        // If current state is initial Pseudo State
    {
      if (ThisEvent.EventType == ES_INIT)    // only respond to ES_Init
      {
        SPI_Init(); //initialize SPI1
        //build up the u8g2 structure with the proper values for our display
        u8g2_Setup_ssd1306_128x64_noname_f(&u8g2, U8G2_R0, u8x8_byte_pic32_hw_spi, 
                                   u8x8_pic32_gpio_and_delay);
        // pass all that stuff on to the display to initialize it
        u8g2_InitDisplay(&u8g2);
        // turn off power save so that the display will be on
        u8g2_SetPowerSave(&u8g2, 0);
        // choose the font. this one is mono-spaced and has reasonable size
        u8g2_SetFont(&u8g2, u8g2_font_t0_18_mr);
        // overwrite the background color of newly written characters
        u8g2_SetFontMode(&u8g2, 0);

        //set display state value for event checker
        LastDisplayState = u8g2_NextPage(&u8g2);

        //transition to available state
        CurrentState = DisplayAvailable;
      }
    }
    break;
    
    /*---------------------------------------------------- DisplayAvailable*/   
    case DisplayAvailable:        // If current state is state one
    {
        if (ThisEvent.EventType == ES_DISPLAY_WELCOME)
        {
            printf("welcome\n\r");
            welcomeScreen();                    // display welcome screen
            CurrentState = DisplayBusy;         // transition to busy state
        }
                
        if (ThisEvent.EventType == ES_DISPLAY_READY)
        {
            printf("ready\n\r");
            round = ThisEvent.EventParam;       // update round
            readyScreen(score, round);          // display ready screen
            CurrentState = DisplayBusy;         // transition to busy state
        }
        
        if (ThisEvent.EventType == ES_DISPLAY_INSTRUCTION)
        {
            printf("instruction\n\r");
            instruction = ThisEvent.EventParam; // update instruction
            instructionScreen(score, round, instruction); // display instruction screen
            CurrentState = DisplayBusy;         //transition to busy state
        }
        
        if (ThisEvent.EventType == ES_DISPLAY_GO)
        {
            printf("go\n\r");
            goScreen(score, round);
            CurrentState = DisplayBusy;
        }
        
        if (ThisEvent.EventType == ES_DISPLAY_PLAY)
        {
            playScreen(0, 15, 0);               // display initial play screen
            CurrentState = DisplayBusy;         //transition to busy state
        }
        
        if (ThisEvent.EventType == ES_DISPLAY_PLAY_UPDATE)
        {
            score = ThisEvent.EventParam;       // update score
            time = ThisEvent.EventParam2;        // update time
            input = ThisEvent.EventParam3;       // update user input
            playScreen(score, time, input);     // display play screen
            CurrentState = DisplayBusy;         // transition to busy state
        }
        
        if (ThisEvent.EventType == ES_DISPLAY_ROUNDCOMPLETE)
        {
            roundCompleteScreen(score, round);  // display round complete screen
            CurrentState = DisplayBusy;         // transition to busy state
        }
        
        if (ThisEvent.EventType == ES_DISPLAY_GAMECOMPLETE)
        {
            gameCompleteScreen(score);          // display game complete screen
            CurrentState = DisplayBusy;         // transition to busy state
        }
    }
    break;
    
    /*--------------------------------------------------------- DisplayBusy*/   
    case DisplayBusy:
    {
        if (ThisEvent.EventType == ES_UPDATE_COMPLETE)
        {
            printf("nextpage\n\r");
            //recall the deferred event 
            ES_RecallEvents(MyPriority, DeferralQueue); 
            //transition to available state
            CurrentState = DisplayAvailable;
        }
        
        if (ThisEvent.EventType == ES_DISPLAY_WELCOME)
        {
            printf("defer\n\r");
            ES_DeferEvent(DeferralQueue, ThisEvent);    // defer event
        }
        
        if (ThisEvent.EventType == ES_DISPLAY_READY)
        {
            printf("defer\n\r");
            ES_DeferEvent(DeferralQueue, ThisEvent);    // defer event
        }
        
        if (ThisEvent.EventType == ES_DISPLAY_PLAY)
        {
            printf("defer\n\r");
            ES_DeferEvent(DeferralQueue, ThisEvent);    // defer event
        }
        
        if (ThisEvent.EventType == ES_DISPLAY_PLAY_UPDATE)
        {
            printf("defer\n\r");
            ES_DeferEvent(DeferralQueue, ThisEvent);    // defer event
        }
        
        if (ThisEvent.EventType == ES_DISPLAY_ROUNDCOMPLETE)
        {
            printf("defer");
            ES_DeferEvent(DeferralQueue, ThisEvent);    // defer event
        }
        
        if (ThisEvent.EventType == ES_DISPLAY_GAMECOMPLETE)
        {
            printf("defer");
            ES_DeferEvent(DeferralQueue, ThisEvent);    // defer event
        }
    }
    break;
    
    // repeat state pattern as required for other states
    default:
      ;
  }                                   // end switch on Current State
  return ReturnEvent;
}

/****************************************************************************
 Function
     QueryDisplay

 Parameters
     None

 Returns
     DisplayState_t The current state of the Template state machine

 Description
     returns the current state of the Display state machine
 Notes

 Author
    A. Gin
****************************************************************************/
DisplayState_t QueryDisplay(void)
{
    return CurrentState;
}

/***************************************************************************
 private functions
 ***************************************************************************/
void welcomeScreen(void)
{
    // clear screen
    u8g2_FirstPage(&u8g2); 
    // write game name to display
    u8g2_DrawStr(&u8g2, 1, 15, " KEEP COPYING "); 
    u8g2_DrawStr(&u8g2, 1, 30, "  AND NOBODY  "); 
    u8g2_DrawStr(&u8g2, 1, 45, "   EXPLODES   ");
    // write start instructions to display
    u8g2_DrawStr(&u8g2, 1, 60, " press button");
    // set last display state to busy
    LastDisplayState = 1;    
}

void readyScreen(uint16_t score, uint16_t round)
{
    // turn round into a string and add it to "R"
    char roundstring[4];
    sprintf(roundstring, "R%i", round);
    
    // turn score into a string
    char scorestring[5];
    sprintf(scorestring, "%i", score);
    
    // clear screen
    u8g2_FirstPage(&u8g2); 
    // write READY to the display
    u8g2_DrawStr(&u8g2, 45, 40, "READY");
    // write the round number to the display
    u8g2_DrawStr(&u8g2, 1, 15, roundstring); 
    // write the score to the display, align text with left side
    if (score < 10)
    {
        u8g2_DrawStr(&u8g2, 120, 15, scorestring);
    }
    else if ((score >= 10) && (score < 100))
    {
        u8g2_DrawStr(&u8g2, 110, 15, scorestring);
    }
    else if ((score >= 100) && (score < 1000))
    {
        u8g2_DrawStr(&u8g2, 100, 15, scorestring);
    }
    else
    {
        u8g2_DrawStr(&u8g2, 90, 15, scorestring);
    }
    // set last display state to busy
    LastDisplayState = 1;
}

void instructionScreen(uint16_t score, uint16_t round, uint16_t instruction)
{
    // turn round into a string and add it to "R"
    char roundstring[4];
    sprintf(roundstring, "R%i", round);
    
    // turn score into a string
    char scorestring[5];
    sprintf(scorestring, "%i", score);
    
    // clear screen
    u8g2_FirstPage(&u8g2); 
    // write the round number to the display
    u8g2_DrawStr(&u8g2, 1, 15, roundstring); 
    // write the score to the display, align text with left side
    if (score < 10)                                 //score is 1 number wide
    {
        u8g2_DrawStr(&u8g2, 120, 15, scorestring);
    }
    else if ((score >= 10) && (score < 100))        // score is 2 numbers wide
    {
        u8g2_DrawStr(&u8g2, 110, 15, scorestring);
    }
    else if ((score >= 100) && (score < 1000))      // score is 3 numbers wide
    {
        u8g2_DrawStr(&u8g2, 100, 15, scorestring);
    }
    else                                            // score is 4 numbers wide
    {
        u8g2_DrawStr(&u8g2, 90, 15, scorestring);
    }
    
    // write the direction to the screen
    if (instruction == 0)   // LEFT
    {
        u8g2_SetFontDirection(&u8g2, 3);            // font direction 270 deg
        u8g2_DrawStr(&u8g2, 65, 15, ">");           // super up arrow
        u8g2_DrawStr(&u8g2, 65, 25, ">");           // up arrow
        u8g2_SetFontDirection(&u8g2, 0);            // reset font direction
           
        u8g2_DrawStr(&u8g2, 28, 40, "<");           // super left arrow
        // highlight on
        u8g2_SetFontMode(&u8g2, 0);   
        u8g2_SetDrawColor(&u8g2, 0); 
        u8g2_DrawStr(&u8g2, 38, 40, "<");           // left arrow
        // highlight off
        u8g2_SetFontMode(&u8g2, 0);                 
        u8g2_SetDrawColor(&u8g2, 1); 
                    
        u8g2_DrawStr(&u8g2, 75, 40, ">");           // right arrow
        u8g2_DrawStr(&u8g2, 85, 40, ">");           // super right arrow  
        
        u8g2_SetFontDirection(&u8g2, 1);            // font direction 90 deg
        u8g2_DrawStr(&u8g2, 55, 45, ">");           // down arrow
        u8g2_DrawStr(&u8g2, 55, 55, ">");           // super down arrow
        u8g2_SetFontDirection(&u8g2, 0);            // reset font direction
    }
    
    if (instruction == 1)   // SUPER LEFT
    {
        u8g2_SetFontDirection(&u8g2, 3);            // font direction 270 deg
        u8g2_DrawStr(&u8g2, 65, 15, ">");           // super up arrow
        u8g2_DrawStr(&u8g2, 65, 25, ">");           // up arrow
        u8g2_SetFontDirection(&u8g2, 0);            // reset font direction
        
        // highlight on
        u8g2_SetFontMode(&u8g2, 0);   
        u8g2_SetDrawColor(&u8g2, 0); 
        u8g2_DrawStr(&u8g2, 28, 40, "<");           // super left arrow
        u8g2_DrawStr(&u8g2, 38, 40, "<");           // left arrow
        // highlight off
        u8g2_SetFontMode(&u8g2, 0);                 
        u8g2_SetDrawColor(&u8g2, 1);
                               
        u8g2_DrawStr(&u8g2, 75, 40, ">");           // right arrow
        u8g2_DrawStr(&u8g2, 85, 40, ">");           // super right arrow
        
        u8g2_SetFontDirection(&u8g2, 1);            // font direction 90 deg
        u8g2_DrawStr(&u8g2, 55, 45, ">");           // down arrow
        u8g2_DrawStr(&u8g2, 55, 55, ">");           // super down arrow
        u8g2_SetFontDirection(&u8g2, 0);            // reset font direction
    }
    
    if (instruction == 2)   // RIGHT
    {
        u8g2_SetFontDirection(&u8g2, 3);            // font direction 270 deg
        u8g2_DrawStr(&u8g2, 65, 15, ">");           // super up arrow
        u8g2_DrawStr(&u8g2, 65, 25, ">");           // up arrow
        u8g2_SetFontDirection(&u8g2, 0);            // reset font direction
        
        u8g2_DrawStr(&u8g2, 28, 40, "<");           // super left arrow
        u8g2_DrawStr(&u8g2, 38, 40, "<");           // left arrow
        
        // highlight on
        u8g2_SetFontMode(&u8g2, 0);   
        u8g2_SetDrawColor(&u8g2, 0);                
        u8g2_DrawStr(&u8g2, 75, 40, ">");           // right arrow
        // highlight off
        u8g2_SetFontMode(&u8g2, 0);                 
        u8g2_SetDrawColor(&u8g2, 1); 
        u8g2_DrawStr(&u8g2, 85, 40, ">");           // super right arrow  
        
        u8g2_SetFontDirection(&u8g2, 1);            // font direction 90 deg
        u8g2_DrawStr(&u8g2, 55, 45, ">");           // down arrow
        u8g2_DrawStr(&u8g2, 55, 55, ">");           // super down arrow
        u8g2_SetFontDirection(&u8g2, 0);            // reset font direction
    }
    
    if (instruction == 3)   // SUPER RIGHT
    {
        u8g2_SetFontDirection(&u8g2, 3);            // font direction 270 deg
        u8g2_DrawStr(&u8g2, 65, 15, ">");           // super up arrow
        u8g2_DrawStr(&u8g2, 65, 25, ">");           // up arrow
        u8g2_SetFontDirection(&u8g2, 0);            // reset font direction
        
        u8g2_DrawStr(&u8g2, 28, 40, "<");           // super left arrow
        u8g2_DrawStr(&u8g2, 38, 40, "<");           // left arrow
        
        // highlight on
        u8g2_SetFontMode(&u8g2, 0);   
        u8g2_SetDrawColor(&u8g2, 0);                
        u8g2_DrawStr(&u8g2, 75, 40, ">");           // right arrow
        u8g2_DrawStr(&u8g2, 85, 40, ">");           // super right arrow
        // highlight off
        u8g2_SetFontMode(&u8g2, 0);                 
        u8g2_SetDrawColor(&u8g2, 1);   
        
        u8g2_SetFontDirection(&u8g2, 1);            // font direction 90 deg
        u8g2_DrawStr(&u8g2, 55, 45, ">");           // down arrow
        u8g2_DrawStr(&u8g2, 55, 55, ">");           // super down arrow
        u8g2_SetFontDirection(&u8g2, 0);            // reset font direction
    }
    
    if (instruction == 4)   // UP
    {
        u8g2_SetFontDirection(&u8g2, 3);            // font direction 270 deg
        u8g2_DrawStr(&u8g2, 65, 15, ">");           // super up arrow
        // highlight on
        u8g2_SetFontMode(&u8g2, 0);   
        u8g2_SetDrawColor(&u8g2, 0); 
        u8g2_DrawStr(&u8g2, 65, 25, ">");           // up arrow
        u8g2_SetFontDirection(&u8g2, 0);            // reset font direction
        // highlight off
        u8g2_SetFontMode(&u8g2, 0);                 
        u8g2_SetDrawColor(&u8g2, 1);
        
        u8g2_DrawStr(&u8g2, 28, 40, "<");           // super left arrow
        u8g2_DrawStr(&u8g2, 38, 40, "<");           // left arrow
                      
        u8g2_DrawStr(&u8g2, 75, 40, ">");           // right arrow
        u8g2_DrawStr(&u8g2, 85, 40, ">");           // super right arrow
        
        u8g2_SetFontDirection(&u8g2, 1);            // font direction 90 deg
        u8g2_DrawStr(&u8g2, 55, 45, ">");           // down arrow
        u8g2_DrawStr(&u8g2, 55, 55, ">");           // super down arrow
        u8g2_SetFontDirection(&u8g2, 0);            // reset font direction
    }
    
    if (instruction == 5)   // SUPER UP
    {
        // highlight on
        u8g2_SetFontMode(&u8g2, 0);   
        u8g2_SetDrawColor(&u8g2, 0);  
        u8g2_SetFontDirection(&u8g2, 3);            // font direction 270 deg
        u8g2_DrawStr(&u8g2, 65, 15, ">");           // super up arrow
        u8g2_DrawStr(&u8g2, 65, 25, ">");           // up arrow
        u8g2_SetFontDirection(&u8g2, 0);            // reset font direction
        // highlight off
        u8g2_SetFontMode(&u8g2, 0);                 
        u8g2_SetDrawColor(&u8g2, 1);
        
        u8g2_DrawStr(&u8g2, 28, 40, "<");           // super left arrow
        u8g2_DrawStr(&u8g2, 38, 40, "<");           // left arrow
                      
        u8g2_DrawStr(&u8g2, 75, 40, ">");           // right arrow
        u8g2_DrawStr(&u8g2, 85, 40, ">");           // super right arrow
        
        u8g2_SetFontDirection(&u8g2, 1);            // font direction 90 deg
        u8g2_DrawStr(&u8g2, 55, 45, ">");           // down arrow
        u8g2_DrawStr(&u8g2, 55, 55, ">");           // super down arrow
        u8g2_SetFontDirection(&u8g2, 0);            // reset font direction
    }
    
    if (instruction == 6)   // DOWN
    {
        u8g2_SetFontDirection(&u8g2, 3);            // font direction 270 deg
        u8g2_DrawStr(&u8g2, 65, 15, ">");           // super up arrow
        u8g2_DrawStr(&u8g2, 65, 25, ">");           // up arrow
        u8g2_SetFontDirection(&u8g2, 0);            // reset font direction
        
        u8g2_DrawStr(&u8g2, 28, 40, "<");           // super left arrow
        u8g2_DrawStr(&u8g2, 38, 40, "<");           // left arrow
                      
        u8g2_DrawStr(&u8g2, 75, 40, ">");           // right arrow
        u8g2_DrawStr(&u8g2, 85, 40, ">");           // super right arrow
        
        // highlight on
        u8g2_SetFontMode(&u8g2, 0);   
        u8g2_SetDrawColor(&u8g2, 0);
        u8g2_SetFontDirection(&u8g2, 1);            // font direction 90 deg
        u8g2_DrawStr(&u8g2, 55, 45, ">");           // down arrow
        // highlight off
        u8g2_SetFontMode(&u8g2, 0);                 
        u8g2_SetDrawColor(&u8g2, 1);
        u8g2_DrawStr(&u8g2, 55, 55, ">");           // super down arrow
        u8g2_SetFontDirection(&u8g2, 0);            // reset font direction
    }
    
    if (instruction == 7)   // SUPER DOWN
    {
        u8g2_SetFontDirection(&u8g2, 3);            // font direction 270 deg
        u8g2_DrawStr(&u8g2, 65, 15, ">");           // super up arrow
        u8g2_DrawStr(&u8g2, 65, 25, ">");           // up arrow
        u8g2_SetFontDirection(&u8g2, 0);            // reset font direction
        
        u8g2_DrawStr(&u8g2, 28, 40, "<");           // super left arrow
        u8g2_DrawStr(&u8g2, 38, 40, "<");           // left arrow
                      
        u8g2_DrawStr(&u8g2, 75, 40, ">");           // right arrow
        u8g2_DrawStr(&u8g2, 85, 40, ">");           // super right arrow
        
        // highlight on
        u8g2_SetFontMode(&u8g2, 0);   
        u8g2_SetDrawColor(&u8g2, 0);
        u8g2_SetFontDirection(&u8g2, 1);            // font direction 90 deg
        u8g2_DrawStr(&u8g2, 55, 45, ">");           // down arrow
        u8g2_DrawStr(&u8g2, 55, 55, ">");           // super down arrow
        u8g2_SetFontDirection(&u8g2, 0);            // reset font direction
        // highlight off
        u8g2_SetFontMode(&u8g2, 0);                 
        u8g2_SetDrawColor(&u8g2, 1);
    }
    
    if (instruction == 8)   // BLANK
    {
        u8g2_SetFontDirection(&u8g2, 3);            // font direction 270 deg
        u8g2_DrawStr(&u8g2, 65, 15, ">");           // super up arrow
        u8g2_DrawStr(&u8g2, 65, 25, ">");           // up arrow
        u8g2_SetFontDirection(&u8g2, 0);            // reset font direction
        
        u8g2_DrawStr(&u8g2, 28, 40, "<");           // super left arrow
        u8g2_DrawStr(&u8g2, 38, 40, "<");           // left arrow
                      
        u8g2_DrawStr(&u8g2, 75, 40, ">");           // right arrow
        u8g2_DrawStr(&u8g2, 85, 40, ">");           // super right arrow
        
        u8g2_SetFontDirection(&u8g2, 1);            // font direction 90 deg
        u8g2_DrawStr(&u8g2, 55, 45, ">");           // down arrow
        u8g2_DrawStr(&u8g2, 55, 55, ">");           // super down arrow
        u8g2_SetFontDirection(&u8g2, 0);            // reset font direction
    }
    
    // set last display state to busy
    LastDisplayState = 1;
}

void goScreen(uint16_t score, uint16_t round)
{
    // turn round into a string and add it to "R"
    char roundstring[4];
    sprintf(roundstring, "R%i", round);
    
    // turn score into a string
    char scorestring[5];
    sprintf(scorestring, "%i", score);
    
    // clear screen
    u8g2_FirstPage(&u8g2); 
    // write READY to the display
    u8g2_DrawStr(&u8g2, 55, 40, "GO!");
    // write the round number to the display
    u8g2_DrawStr(&u8g2, 1, 15, roundstring); 
    // write the score to the display, align text with left side
    if (score < 10)                                 // score is 1 number wide
    {
        u8g2_DrawStr(&u8g2, 120, 15, scorestring);
    }
    else if ((score >= 10) && (score < 100))        // score is 2 numbers wide
    {
        u8g2_DrawStr(&u8g2, 110, 15, scorestring);
    }
    else if ((score >= 100) && (score < 1000))      // score is 3 numbers wide
    {
        u8g2_DrawStr(&u8g2, 100, 15, scorestring);
    }
    else                                            // score is 4 numbers wide
    {
        u8g2_DrawStr(&u8g2, 90, 15, scorestring);
    }
    // set last display state to busy
    LastDisplayState = 1;
}

void playScreen(uint16_t score, uint16_t time, uint16_t input)
{

}

void roundCompleteScreen(uint16_t score, uint16_t round)
{
    // turn round into a string and add it to "R"
    char roundstring[4];
    sprintf(roundstring, "R%i", round);
    
    // turn score into a string
    char scorestring[5];
    sprintf(scorestring, "%i", score);
    
    // clear screen
    u8g2_FirstPage(&u8g2); 
    // write READY to the display
    u8g2_DrawStr(&u8g2, 7, 40, "BOMB DEFUSED!");
    // write the round number to the display
    u8g2_DrawStr(&u8g2, 1, 15, roundstring); 
    // write the score to the display, align text with left side
    if (score < 10)                                 // score is 1 number wide
    {
        u8g2_DrawStr(&u8g2, 120, 15, scorestring);
    }
    else if ((score >= 10) && (score < 100))        // score is 2 numbers wide
    {
        u8g2_DrawStr(&u8g2, 110, 15, scorestring);
    }
    else if ((score >= 100) && (score < 1000))      // score is 3 numbers wide
    {
        u8g2_DrawStr(&u8g2, 100, 15, scorestring);
    }
    else                                            // score is 4 numbers wide
    {
        u8g2_DrawStr(&u8g2, 90, 15, scorestring);
    }
    
    // set last display state to busy
    LastDisplayState = 1;
}

void gameCompleteScreen(uint16_t score)
{
    // clear screen
    u8g2_FirstPage(&u8g2); 
    // write GAME OVER to the display
    u8g2_DrawStr(&u8g2, 85, 35, "GAME");
    u8g2_DrawStr(&u8g2, 85, 50, "OVER");
    // write High Scores to the display
    u8g2_DrawStr(&u8g2, 1, 12, "High Scores");
    
    //get high score values
    char score1[8] = "1. 4000";
    char score2[8] = "2. 3000";
    char score3[8] = "3. 2000";
    
    // write high score values to displayed
    u8g2_DrawStr(&u8g2, 1, 30, score1);
    u8g2_DrawStr(&u8g2, 1, 45, score2);
    u8g2_DrawStr(&u8g2, 1, 60, score3);
    
    // set last display state to busy
    LastDisplayState = 1;
}


/***************************************************************************
 event checkers
 ***************************************************************************/
bool Check4WriteDone(void)
{
  uint8_t         CurrentDisplayState;
  bool            ReturnVal = false;
  
  if (CurrentState == DisplayBusy){
  CurrentDisplayState = u8g2_NextPage(&u8g2);
  
      // check for display done AND different from last time
      if ((LastDisplayState != CurrentDisplayState) &&(CurrentDisplayState == 0)) 
      {
        // Post event to OLEDService0
        ES_Event_t ThisEvent;
        ThisEvent.EventType   = ES_UPDATE_COMPLETE;
        ThisEvent.EventParam  = 1;
        ES_PostToService(MyPriority, ThisEvent);
        ReturnVal = true;
      }
      LastDisplayState = CurrentDisplayState; // update the state for next time
    }
    return ReturnVal;
}