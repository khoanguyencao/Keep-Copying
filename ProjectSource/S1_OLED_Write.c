#include "../ProjectHeaders/S1_OLED_Write.h"

// Hardware
#include <xc.h>
#include <stdlib.h>
#include <string.h>
#include <proc/p32mx170f256b.h>
#include <sys/attribs.h> // for ISR macors
#include "EventCheckers.h"

// Event & Services Framework
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "ES_DeferRecall.h"
#include "ES_ShortTimer.h"
#include "ES_Port.h"

//OLED headers
#include "../u8g2Headers/u8g2TestHarness_main.h"
#include "../u8g2Headers/common.h"
#include "../u8g2Headers/spi_master.h"
#include "../u8g2Headers/u8g2.h"
#include "../u8g2Headers/u8x8.h"


/*---------------------------- Module Variables ---------------------------*/
// with the introduction of Gen2, we need a module level Priority variable
static uint8_t MyPriority;
// add a deferral queue for up to 3 pending deferrals +1 to allow for overhead
static ES_Event_t DeferralQueue[3 + 1];

//OLED Variables
extern uint8_t u8x8_pic32_gpio_and_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
extern uint8_t u8x8_byte_pic32_hw_spi(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);

static u8g2_t u8g2;

static uint16_t offset=0; // start at the rightmost character position

static State_t Current_State; //Variable for current state of machine

/*Variables for manipulating string output to OLED*/
const char lineBuffer[] = "               "; //15 blank spaces

static char ENHlineBuffer[15]; //Variable input to DrawStr function

static uint8_t counter = 0; //Counter for calculation required offset

static uint8_t lastPage = 0; //Variable for event checking function
/*------------------------------ Module Code ------------------------------*/

/****************************************************************************
 Function
     S1_OLED_Write
 Parameters
     uint8_t : the priorty of this service
 Returns
     bool, false if error in initialization, true otherwise
 Description
     Initialize systems, SPI, OLED, Set current state to PSINIT
****************************************************************************/

bool InitS1_OLED_Write(uint8_t Priority)
{    
  ES_Event_t ThisEvent;

  MyPriority = Priority;
  //Initialization Code for initializing system, SPI, and OLED
    // sysInit is used for timing setup for the test harness
  
    sysInit();
    SPI_Init(); 
    
    // build up the u8g2 structure with the proper values for our display
    u8g2_Setup_ssd1306_128x64_noname_f(&u8g2, U8G2_R0, u8x8_byte_pic32_hw_spi, 
                                       u8x8_pic32_gpio_and_delay);
    // pass all that stuff on to the display to initialize it
    u8g2_InitDisplay(&u8g2);
    // turn off power save so that the display will be on
    u8g2_SetPowerSave(&u8g2, 0);
    // choose the font. this one is mono-spaced and has a reasonable size
    u8g2_SetFont(&u8g2, u8g2_font_t0_18_mr);
    // overwrite the background color of newly written characters
    u8g2_SetFontMode(&u8g2, 0);
    
    // initialize deferral queue for testing Deferal function
    ES_InitDeferralQueueWith(DeferralQueue, ARRAY_SIZE(DeferralQueue));
    
  // post the initial transition event
  Current_State = NOT_BUSY;
  ThisEvent.EventType = ES_PRESS;
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
     PostS1_OLED_Write
 Parameters
     EF_Event ThisEvent ,the event to post to the queue
 Returns
     bool false if the queue operation failed, true otherwise
 Description
     Posts an event to this state machine's queue
****************************************************************************/
bool PostS1_OLED_Write(ES_Event_t ThisEvent)
{
  return ES_PostToService(MyPriority, ThisEvent);
}

/****************************************************************************
 Function
    RunS1_OLED_Write
 Parameters
   ES_Event : the event to process
 Returns
   ES_Event, ES_NO_EVENT if no error ES_ERROR otherwise
 Description
   add your description here

****************************************************************************/
ES_Event_t RunS1_OLED_Write(ES_Event_t ThisEvent)
{
  ES_Event_t ReturnEvent;
  ReturnEvent.EventType = ES_NO_EVENT; // assume no errors
/*-----------------------------------------------------------------------------
 * Current State switch case statement, Compares NOT BUSY, WRITING
 * --------------------------------------------------------------------------*/
  
    //Event deferral recall, must be call before ES_RUN enters if statements
    ES_RecallEvents(MyPriority, DeferralQueue);
    if (Current_State == NOT_BUSY)   
    {
        //Write to oled upon receipt of event
        if (ThisEvent.EventType == ES_WRITE)
        {
            ENHlineBuffer[14]=(char)ThisEvent.EventParam;
            //printf(" text %s \r\n", ENHlineBuffer);
            /*First page and DrawStr functions to update OLED screen*/
            u8g2_FirstPage(&u8g2);
            u8g2_DrawStr(&u8g2, offset, 37, ENHlineBuffer);

            /*Setting Event Checking variable to true, due to speed of
              u8g2 Next Page function. This ensures that when the event checker
              looks at the variable and the Next page function, 
              the OLED has completed drawing operations----------------------*/
            lastPage = 1;
            Current_State = WRITING; //Set current state to writing
        }
        //Event for notifying user that program is calibrating
        else if (ThisEvent.EventType == ES_PRESS)
        {
            //Initialize Enhance line buffer
            lineBufferENH(lineBuffer);
            /*First page and DrawStr functions to update OLED screen*/
            u8g2_FirstPage(&u8g2);
            u8g2_DrawStr(&u8g2, 20, 37, "CALIBRATING");

            /*Setting Event Checking variable to true, due to speed of
              u8g2 Next Page function. This ensures that when the event checker
              looks at the variable and the Next page function, 
              the OLED has completed drawing operations----------------------*/
            lastPage = 1;
            Current_State = WRITING; //Set current state to writing
        }
    }
    else if (Current_State ==  WRITING)  
    {
        /*Event deferral sorting to respond to 2 ES_WRITE that are incoming
         at the same time, in this case the second event contains blank space*/
        if (' ' == (char)ThisEvent.EventParam)
        {
            ES_DeferEvent(DeferralQueue, ThisEvent);
        }
        //Writing has completed, scroll message
        if (ThisEvent.EventType == ES_XFER_C)
        {
            static uint8_t i;
            for(i=0;i<14;i++)
            {
                ENHlineBuffer[i]=ENHlineBuffer[i+1];
            }
            Current_State = NOT_BUSY;
        }
    }
    else {}
  

  return ReturnEvent;
}

/*Event Checking Function-----------------------------------------------------
 Determines if OLED has completed writing to the screen
 Accepts nothing , returns bool for processor
 Checks if the Current State  = Writing to minimize call of Next Page
 if there is a difference between next page and last page, 
 post event, writing has completed
 ----------------------------------------------------------------------------*/
    
bool NextPage(void)
{
    static ES_Event_t ThisEvent;
    static uint8_t Next_Page;
    static bool RetVal = false; //return val
    
    if (Current_State == WRITING)
    {
        //check state of next page function
        //0 means OLED is not busy
        //1 means OLED is still drawing 
        Next_Page = u8g2_NextPage(&u8g2);

        if ((lastPage == 1) && (Next_Page == 0))
        {
            //A change was detected in NextPage
            lastPage = 0; //Reset Event checking variable
            ThisEvent.EventType = ES_XFER_C;
            PostS1_OLED_Write(ThisEvent); //Post XFER C event
            //printf("XFER sent from event \r\n");
            RetVal = true;
        } 
    }
    return RetVal;
}


/*Function to divide large strings into chunks for OLED display*/
void lineBufferENH(const char *str)
{

    static uint8_t i;
    //For strings  < 15 character, pass the original string
        for(i=0;i<15;i++)
        {
            ENHlineBuffer[i]=*(str +i);
        }
}