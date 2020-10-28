#include "Seq.h"
//Hardware
#include <xc.h>
#include <proc/p32mx170f256b.h>
#include <sys/attribs.h> // for ISR macors
#include <stdio.h>
#include <stdlib.h>

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

static uint8_t seq_array[150]; //array containing random directions
//static uint8_t *ps_array = seq_array; //pointer to seq_array
static uint8_t sl=4; //counter variable that contains length of array
static uint32_t score=0; //initial player score
static uint8_t seq_idx=0; //Sequence Index 
static uint8_t play_time = 0; //Play time counter
static uint8_t round = 1; //Round number
static uint8_t display_c=1; // Display counter, for demonstrating sequence

static SState_t Current_State; //State Machine Current State Variable

/*------------------------------ Module Code ------------------------------*/

/****************************************************************************
 Function
    
 Parameters
     uint8_t : the priorty of this service
 Returns
     bool, false if error in initialization, true otherwise
 Description
     Initialize systems, SPI, OLED, Set current state to PSINIT
****************************************************************************/

bool InitSequence(uint8_t Priority)
{    
  ES_Event_t ThisEvent;

  MyPriority = Priority;
   
  //Clear sequence Array
  
  //Set current State
  Current_State = SequenceCreate;
  // post the initial transition event
  ThisEvent.EventType = ES_FIRST_ROUND;
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

 Parameters
     EF_Event ThisEvent ,the event to post to the queue
 Returns
     bool false if the queue operation failed, true otherwise
 Description
     Posts an event to this state machine's queue
****************************************************************************/
bool PostSequence(ES_Event_t ThisEvent)
{
  return ES_PostToService(MyPriority, ThisEvent);
}

/****************************************************************************
 Function

 Parameters
   ES_Event : the event to process
 Returns
   ES_Event, ES_NO_EVENT if no error ES_ERROR otherwise
 Description
   add your description here

****************************************************************************/
ES_Event_t RunSequence(ES_Event_t ThisEvent)
{
  ES_Event_t ReturnEvent;
  ReturnEvent.EventType = ES_NO_EVENT; // assume no errors
/*-----------------------------------------------------------------------------
 * Current State switch case statement, Compares NOT BUSY, WRITING
 * --------------------------------------------------------------------------*/

    switch(Current_State)
    {
        case SequenceCreate:
        {
            switch (ThisEvent.EventType)
            {
                case ES_FIRST_ROUND:
                {
                    //Clear Array
                    //Init Array length, round, and score 
                    sl =4;
                    score=0;
                    round = 1;
                    
                    
                    //Sequence Random initialization
                    static uint8_t i;
                    for(i=0;i<sl;i++)
                    {
                        seq_array[i]=(rand() % 8); //populate new array element
                    }
                    seq_idx=0; //Initial sequence index
                    
                    printf("sequence %d \r\n",seq_array[0]);
                    printf("sequence %d \r\n",seq_array[1]);
                    printf("sequence %d \r\n",seq_array[2]);
                    printf("sequence %d \r\n",seq_array[3]);
                }
                break;
                
                case ES_NEXT_ROUND:
                {
                    seq_array[sl]=(rand() % 8); //populate new array element
                    sl++; //Increment Array size
                    round++; //Increment Round number
                    
                    seq_idx=0; //Initial sequence index
                    
                    printf("sequence %d \r\n",seq_array[0]);
                    printf("sequence %d \r\n",seq_array[1]);
                    printf("sequence %d \r\n",seq_array[2]);
                    printf("sequence %d \r\n",seq_array[3]);
                    printf("sequence %d \r\n",seq_array[4]);
                }
                break;
                
                case ES_TIMEOUT: //need to change to an event from key mapper
                {
                        printf("Direction %d \r\n", seq_array[0]); 
                        //Use printf to debug, here goes the posting to oled

                        //Initialize timer for displaying sequence, This timer
                        //Posts to myself to continue displaying sequence
                        ES_Timer_InitTimer(DIRECTION_TIMER, 500);
                        Current_State=SequenceDisplay; //Transition to Seq_Display
                }
                break;
                
                default:{} break;
            }
        }
        break;
        
        case SequenceDisplay:
        {
            //Initialize counter for keeping track of how many array elements
            //have been displayed to the user, and begin a transition to 
            //the GO screen
            
            switch(ThisEvent.EventType)
            {
                case ES_TIMEOUT:
                {
                    //This part deals with the TimeOut event from GO Screen
                    switch (ThisEvent.EventParam)
                    {
                        case 13:
                        {
                            if(display_c < sl-1)
                            {
                                printf("Direction %d \r\n", seq_array[display_c]); 
                                //Use printf to debug, here goes the posting to oled

                                //Initialize timer for displaying sequence, This timer
                                //Posts to myself to continue displaying sequence
                                ES_Timer_InitTimer(DIRECTION_TIMER, 500);

                                //Increase counter
                                display_c++;
                            }
                            else if (display_c == (sl-1))
                            {
                                printf("Direction %d \r\n", seq_array[display_c]); 
                                //Use printf to debug, here goes the posting to oled

                                /*----------------------------------------------------
                                 * Initialize timer for displaying sequence, This timer
                                 * post to Game SM to proceed to GO screen
                                 * --------------------------------------------------*/
                                ES_Timer_InitTimer(LAST_DIRECTION_TIMER, 500);
                                //Notice that is a different Timer

                                //Reset Counter
                                display_c = 1;
                            }
                        }
                        break;
                        
                        case 10://10 is timer # for GO_TIMER
                        {
                            //Post to OLED to display gameplay screen
                            //Remember to ES_Event_t ThisEvent.EventType...
                            printf("GAMEPLAY SCREEN\r\n");
                            //Transition to next State
                            Current_State = SequenceInput;
                            //Start 1 s Input Timer
                            ES_Timer_InitTimer(INPUT_TIMER, 1000);
                            //Set play time elapse to 0 s
                            play_time = 0;
                        }
                        break;
                        
                        default:{} break;
                    }    
                }
                break;
                
                default:{} break;
            }
            
        }
        break;
        
        case SequenceInput:
        {
            switch (ThisEvent.EventType)
            {
                case ES_TIMEOUT:
                {
                    if (play_time < 14)
                    {
                        //Restart Timer
                        ES_Timer_InitTimer(INPUT_TIMER, 1000);
                        //Post to OLED screen
                        //Remember ES_Event_t ThisEvent.....
                        printf("-1 sec \r\n");
                        play_time++;                        
                    }
                    else if (play_time == 14)
                    {
                        //Post to OLED to transition to game over
                        //Post to myself to transition
                        ThisEvent.EventType = ES_FIRST_ROUND;
                        PostSequence(ThisEvent);
                        
                        //Update Current State
                        Current_State = SequenceCreate;
                        
                        printf("timeout gameover\r\n");
                    }  
                }
                break;

                case ES_INCORRECT_INPUT:
                {
                    //Post to OLED to transition to game over
                    //Post to myself to transition
                    ThisEvent.EventType = ES_FIRST_ROUND;
                    PostSequence(ThisEvent);

                    //Update Current State
                    Current_State = SequenceCreate;
                    
                    printf("input gameover\r\n");
                }
                break;
                
                case ES_CORRECT_INPUT_F://this is sent from the event checker
                {
                    //Post to OLED to transition to Round Complete
                    //Post to myself to transition
                    ThisEvent.EventType = ES_NEXT_ROUND;
                    PostSequence(ThisEvent);

                    //Update Current State
                    Current_State = SequenceCreate;
                    
                    printf("input round won\r\n");
                }
                break;
                
                case ES_CORRECT_INPUT://this is sent from the event checker
                {
                    //Increment Score
                    if (sl<=4)
                    {
                        score=score+10;
                    }
                    else
                    {
                        score=score+(sl/4)*10;
                    }
                    //Post to OLED to transition to Round Complete
                    
                    //Increment Sequence Index
                    seq_idx++; //This sequence index begins at zero
                    
                    printf("input correct\r\n");
                }
                break;
                
                default:{} break;
            }
        }
        break;
        
        default:{} break;
    }

  return ReturnEvent;
}

/*Event Checking Function-----------------------------------------------------

 ----------------------------------------------------------------------------*/
    