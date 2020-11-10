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
 10/30/20       kcao    Integration with GameState and Seq
 10/28/20 07:59 acg     first pass
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

// OLED
#include "../u8g2Headers/common.h"
#include "../u8g2Headers/spi_master.h"
#include "../u8g2Headers/u8g2.h"
#include "../u8g2Headers/u8x8.h"

// My Modules
#include "Display.h"
#include "GameState.h"



/*----------------------------- Module Defines ----------------------------*/

/*---------------------------- Module Functions ---------------------------*/
/* prototypes for private functions for this machine.They should be functions
   relevant to the behavior of this state machine
*/
static void welcomeScreen(void);
static void readyScreen(uint16_t score, uint16_t round);
static void instructionScreen(uint16_t score, uint16_t round, uint16_t instruction);
static void goScreen(uint16_t score, uint16_t round);
static void playScreen(uint16_t score, uint8_t time, uint8_t input);
static void roundCompleteScreen(uint16_t score, uint16_t round);
static void gameCompleteScreen(void);
void demoScreen(void);
static void bitUnpack(uint16_t EventParam, uint16_t* score, uint8_t* time, uint8_t* input);

/*---------------------------- Module Variables ---------------------------*/
// everybody needs a state variable, you may need others as well.
// type of state variable should match that of enum in header file
static DisplayState_t CurrentState;
static uint8_t LastDisplayState;

// keep track of values needing to be written on the display
static uint16_t score;
static uint8_t time = 15;
static uint8_t input = 8;
static uint16_t round = 1;
static uint16_t instruction;
uint16_t score1;
uint16_t score2;
uint16_t score3;

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
    case DisplayInitPState:        
    {
      if (ThisEvent.EventType == ES_INIT)  
      {
        SPI_Init_Display(); //initialize SPI1
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
    case DisplayAvailable:        
    {
        if (ThisEvent.EventType == ES_DISPLAY_WELCOME)
        {
            welcomeScreen();                    // display welcome screen
            score = 0;
            CurrentState = DisplayBusy;         // transition to busy state
        }
                
        if (ThisEvent.EventType == ES_DISPLAY_READY)
        {
            round = ThisEvent.EventParam;       // update round
            readyScreen(score, round);          // display ready screen
            CurrentState = DisplayBusy;         // transition to busy state
        }
        
        if (ThisEvent.EventType == ES_DISPLAY_INSTRUCTION)
        {
            instruction = ThisEvent.EventParam; // update instruction
            instructionScreen(score, round, instruction); // display instruction screen
            CurrentState = DisplayBusy;         //transition to busy state
        }
        
        if (ThisEvent.EventType == ES_DISPLAY_GO)
        {
            goScreen(score, round);             // display go screen
            CurrentState = DisplayBusy;         // transition to busy state
        }
        
        if (ThisEvent.EventType == ES_DISPLAY_PLAY_UPDATE)
        {
            bitUnpack(ThisEvent.EventParam, &score, &time, &input);
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
            gameCompleteScreen();               // display game complete screen
            CurrentState = DisplayBusy;         // transition to busy state
        }
        
        if (ThisEvent.EventType == ES_DISPLAY_DEMO)
        {
            demoScreen();                       // display demo screen
            CurrentState = DisplayBusy;         // transition to busy state
        }
    }
    break;
    
    /*--------------------------------------------------------- DisplayBusy*/   
    case DisplayBusy:
    {
        if (ThisEvent.EventType == ES_UPDATE_COMPLETE)
        {
            //recall the deferred event 
            ES_RecallEvents(MyPriority, DeferralQueue); 
            //transition to available state
            CurrentState = DisplayAvailable;
        }
        
        if (ThisEvent.EventType == ES_DISPLAY_WELCOME)
        {
            ES_DeferEvent(DeferralQueue, ThisEvent);    // defer event
        }
        
        if (ThisEvent.EventType == ES_DISPLAY_READY)
        {
            ES_DeferEvent(DeferralQueue, ThisEvent);    // defer event
        }
        
        if (ThisEvent.EventType == ES_DISPLAY_INSTRUCTION)
        {
            ES_DeferEvent(DeferralQueue, ThisEvent);    // defer event
        }
        
        if (ThisEvent.EventType == ES_DISPLAY_PLAY_UPDATE)
        {
            ES_DeferEvent(DeferralQueue, ThisEvent);    // defer event
        }
        
        if (ThisEvent.EventType == ES_DISPLAY_ROUNDCOMPLETE)
        {
            ES_DeferEvent(DeferralQueue, ThisEvent);    // defer event
        }
        
        if (ThisEvent.EventType == ES_DISPLAY_GAMECOMPLETE)
        {
            ES_DeferEvent(DeferralQueue, ThisEvent);    // defer event
        }
        
        if (ThisEvent.EventType == ES_DISPLAY_DEMO)
        {
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
//Creates and displays the Welcome 
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

// Creates and displays the Ready screen
void readyScreen(uint16_t score, uint16_t round)
{
    // multiply score by 10 to get actual score
    score = score * 10;
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
    if (score < 10)                                 //score is 1 number wide
    {
        u8g2_DrawStr(&u8g2, 120, 15, scorestring);
    }
    else if ((score >= 10) && (score < 100))        //score is 2 numbers wide
    {
        u8g2_DrawStr(&u8g2, 110, 15, scorestring);  
    }
    else if ((score >= 100) && (score < 1000))      //score is 3 numbers wide
    {
        u8g2_DrawStr(&u8g2, 100, 15, scorestring);
    }
    else                                            //score is 4 numbers wide
    {
        u8g2_DrawStr(&u8g2, 90, 15, scorestring);
    }
    // set last display state to busy
    LastDisplayState = 1;
}

// Creates and displays the Instruction screen
void instructionScreen(uint16_t score, uint16_t round, uint16_t instruction)
{
    // turn round into a string and add it to "R"
    char roundstring[4];
    sprintf(roundstring, "R%i", round);
    
    // turn score into a string
    score = score * 10;
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

// Creates and displays the Go screen
void goScreen(uint16_t score, uint16_t round)
{
    // turn round into a string and add it to "R"
    score = score * 10;
    char roundstring[4];
    sprintf(roundstring, "R%i", round);
    
    // turn score into a string
    char scorestring[5];
    sprintf(scorestring, "%i", score);
    
    // clear screen
    u8g2_FirstPage(&u8g2); 
    // write GO to the display
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

// Creates and displays the Play screen
void playScreen(uint16_t score, uint8_t time, uint8_t input)
{
    // turn round into a string and add it to "R"
    char roundstring[4];
    sprintf(roundstring, "R%i", round);
    
    // multiply score by 10 and turn score into a string
    score = score * 10;
    char scorestring[5];
    sprintf(scorestring, "%i", score);
    
    // turn time into a string
    char timestring[3];
    sprintf(timestring, "%i", time);
    
    // clear screen
    u8g2_FirstPage(&u8g2); 
    // write the round number to the display
    u8g2_DrawStr(&u8g2, 1, 15, roundstring); 
    
    // write the time to the display
    if (time < 10)                                  // time is 1 number wide
    {
        u8g2_DrawStr(&u8g2, 120, 60, timestring); 
    }
    if ((time >= 10) && (time <= 15))               // time is 2 numbers wide
    {
        u8g2_DrawStr(&u8g2, 110, 60, timestring); 
    }
    
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
    if (input == 0)   // LEFT
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
    
    if (input == 1)   // SUPER LEFT
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
    
    if (input == 2)   // RIGHT
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
    
    if (input == 3)   // SUPER RIGHT
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
    
    if (input == 4)   // UP
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
    
    if (input == 5)   // SUPER UP
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
    
    if (input == 6)   // DOWN
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
    
    if (input == 7)   // SUPER DOWN
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
    
    if (input == 8)   // BLANK
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

// Creates and displays the Round Complete screen
void roundCompleteScreen(uint16_t score, uint16_t round)
{
    // turn round into a string and add it to "R"
    char roundstring[4];
    sprintf(roundstring, "R%i", round);
    
    // multiply score by 10 and turn score into a string
    score = score * 10;
    char scorestring[5];
    sprintf(scorestring, "%i", score);
    
    // clear screen
    u8g2_FirstPage(&u8g2); 
    // write BOMB DEFUSED! to the display
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
    // write press button to the display
    u8g2_DrawStr(&u8g2, 1, 60, " press button");
    // set last display state to busy
    LastDisplayState = 1;
}

// Creates and displays the Game Complete screen
void gameCompleteScreen(void)
{
    // clear screen
    u8g2_FirstPage(&u8g2); 
    // write GAME OVER to the display
    u8g2_DrawStr(&u8g2, 85, 35, "GAME");
    u8g2_DrawStr(&u8g2, 85, 50, "OVER");
    // write High Scores to the display
    u8g2_DrawStr(&u8g2, 1, 12, "High Scores");
    
    //get high score values and turn into strings
    queryHighScores(&score1, &score2, &score3);
    score1 = score1 * 10;
    score2 = score2 * 10;
    score3 = score3 * 10;
    char score1string[8];
    sprintf(score1string, "1. %i", score1);
    char score2string[8];
    sprintf(score2string, "2. %i", score2);
    char score3string[8];
    sprintf(score3string, "3. %i", score3);
    
    // write high score values to display
    u8g2_DrawStr(&u8g2, 1, 30, score1string);
    u8g2_DrawStr(&u8g2, 1, 45, score2string);
    u8g2_DrawStr(&u8g2, 1, 60, score3string);
    
    // set last display state to busy
    LastDisplayState = 1;
}

// creates and displays the demo screen
void demoScreen(void)
{
    // clear screen
    u8g2_FirstPage(&u8g2); 
    // write DEMO to display
    u8g2_DrawStr(&u8g2, 4, 40, "     DEMO    "); 
    // set last display state to busy
    LastDisplayState = 1;    
}

// Needs to pass score, time and input by reference 
// (i.e. bitUnpack (EventParam, &score, &time, &input))
// Note which params are uint16_t vs uint8_t - will need to initialize correctly 
static void bitUnpack(const uint16_t EventParam, uint16_t* score, uint8_t* time, uint8_t* input){
    uint8_t fourBitMask = ((BIT0HI) | (BIT1HI) | (BIT2HI) | (BIT3HI));
    *input = EventParam & fourBitMask;
    *time = (EventParam >> 4) & fourBitMask;
    *score = EventParam >> 8;
}


/***************************************************************************
 event checkers
 ***************************************************************************/
bool Check4WriteDone(void)
{
  uint8_t         CurrentDisplayState;
  bool            ReturnVal = false;
  
  if (CurrentState == DisplayBusy){     // only check when display is busy
  CurrentDisplayState = u8g2_NextPage(&u8g2);
  
      // check for display done AND different from last time
      if ((LastDisplayState != CurrentDisplayState) &&(CurrentDisplayState == 0)) 
      {
        // Post event to Display Service
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