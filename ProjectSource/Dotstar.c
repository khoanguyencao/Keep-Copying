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

/*---------------------------- Module Functions ---------------------------*/
/* prototypes for private functions for this machine.They should be functions
   relevant to the behavior of this state machine
*/

/*---------------------------- Module Variables ---------------------------*/
// everybody needs a state variable, you may need others as well.
// type of state variable should match that of enum in header file
static DotstarState_t CurrentState;

// keep track of values needing to be written on the display


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
  printf("init func\n\r");
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
  ES_Event_t ReturnEvent;
  ReturnEvent.EventType = ES_NO_EVENT; // assume no errors

  switch (CurrentState)
  {
    /*---------------------------------------------------------- InitPState*/   
    case DotstarInitPState:        
    {
        if (ThisEvent.EventType == ES_INIT)
        {
            //initialize SPI for dotstar
            dotStarSPI_Init();
            
            //enable SPI operation by setting the ON bit
            SPI1CONbits.ON = 1;
            //transition to next case
            CurrentState = DotstarRed;
            ThisEvent.EventType = ES_RED;
            ES_PostToService(MyPriority, ThisEvent);
            printf("dotstar initialized\n\r");
        }
    }
    break;
    
    /*---------------------------------------------------- DisplayAvailable*/   
    case DotstarRed:        
    {
        //dotStar_Write(0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00);
        if (ThisEvent.EventType == ES_RED)
        {
            printf("if red\n\r");
            dotStar_Write(0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00);
        }
    }
    break;
    
    /*--------------------------------------------------------- DisplayBusy*/   
    case DotstarGreen:
    {
        
    }
    break;
    
    case DotstarRandom:
    {
        
    }
    break;
    
    case DotstarOff:
    {
        
    }
    break;
    
    default:
      ;
  }                                   // end switch on Current State
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
void dotStarSPI_Init(){
    uint8_t bitWidth = 32;
    uint16_t bitRate = 10000;
    uint8_t clearbuff;

    //disable analog function on all SPI pins
    ANSELAbits.ANSA0 = 0;   //RA0
    ANSELBbits.ANSB1 = 0;   //RB1
    ANSELBbits.ANSB15 = 0;  //RB15

    //map SDO, SCK, and SS outputs to desired pins
    RPA0R = 0b0011; //set RA0 as SS*
    TRISAbits.TRISA0 = 0; //set RA0 as output
    
    RPB5R = 0b0011; //set RB5 as SDO
    TRISBbits.TRISB5 = 0; //set RB5 as output
    
    TRISBbits.TRISB15 = 0; //set RB15 as output, RB15 is always set to SCK

    //stop and reset SPI module by clearing the ON bit
    SPI1CONbits.ON = 0;

    //clear the receive buffer
    clearbuff = SPI1BUF;

    //set the ENHBUF bit to use enhanced buffer mode
    SPI1CONbits.ENHBUF = 1;

    //write the baud rate register
    SPI1BRG = ((10*10^6) / bitRate) - 1;

    //clear the SPIROV bit
    SPI1STATbits.SPIROV = 0;

    //write desired settings
    if (bitWidth == 8){
        SPI1CONbits.MODE32 = 0; //turn off 32 bit transfer mode
        SPI1CONbits.MODE16 = 0; //turn off 16 bit transfer mode
    }
    else if (bitWidth == 16){
        SPI1CONbits.MODE32 = 0; //turn off 32 bit transfer mode
        SPI1CONbits.MODE16 = 1; //turn on 16 bit transfer mode
    }
    else if (bitWidth == 32){
        SPI1CONbits.MODE32 = 1; //turn on 32 bit transfer mode
        SPI1CONbits.MODE16 = 0; //turn off 16 bit transfer mode
    }

    SPI1CONbits.CKE = 0; //set 2nd clock edge as active
    SPI1CONbits.CKP = 1; //set clock idle high
    SPI1CONbits.MSTEN = 1; //enable master mode
    SPI1CONbits.MSSEN = 1; //slave select enabled
    SPI1CONbits.MCLKSEL = 0; //set MCLK as peripheral bus CLK
    SPI1CONbits.SMP = 0; //input data sampled at middle of data output time
    SPI1CONbits.FRMPOL = 0; //frame pulse or SS pin is active low
    SPI1CONbits.FRMEN = 0; //framed SPI support is disabled
    SPI1CONbits.DISSDI = 0; //SDI pin controlled by SPI module

    //enable SPI operation by setting the ON bit
    SPI1CONbits.ON = 1;
}

void dotStar_Write(uint8_t Bright1, uint8_t Red1, uint8_t Blue1, uint8_t Green1, 
            uint8_t Bright2, uint8_t Red2, uint8_t Blue2, uint8_t Green2){
    uint32_t data;
    //write start frame
    SPI_Write(0x00000000);
    
    //write first LED to full intensity white
    data = ((Bright1 << 24) | (Blue1 << 16) | (Green1 << 8) | (Red1));
    SPI_Write(data);
    
    //write second LED to full intensity red
    data = ((Bright2 << 24) | (Blue2 << 16) | (Green2 << 8) | (Red2));
    SPI_Write(data);
    
    //write reset frame
    SPI_Write(0x00000000);
    
    //wait for buffer to not be full
    while (!SPI_HasXmitBufferSpaceOpened()){
    }
    
    //write end frame
    SPI_Write(0xFFFFFFFF);
}