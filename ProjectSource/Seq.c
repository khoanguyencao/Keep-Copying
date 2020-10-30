#include "Seq.h"
#include "PIC32_AD_Lib.h"
// Hardware
#include <xc.h>
#include <proc/p32mx170f256b.h>
#include <sys/attribs.h> // for ISR macors
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Event & Services Framework
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "ES_DeferRecall.h"
#include "ES_ShortTimer.h"
#include "ES_Port.h"

// OLED headers
#include "../u8g2Headers/u8g2TestHarness_main.h"
#include "../u8g2Headers/common.h"
#include "../u8g2Headers/spi_master.h"
#include "../u8g2Headers/u8g2.h"
#include "../u8g2Headers/u8x8.h"

// Game Services
#include "GameState.h"

/*----------------------------- Module Defines ----------------------------*/

#define ROUND_TIME 15
/*---------------------------- Module Functions ---------------------------*/
/* prototypes for private functions for this machine.They should be functions
   relevant to the behavior of this state machine
*/


/*---------------------------- Module Variables ---------------------------*/
// with the introduction of Gen2, we need a module level Priority variable
static uint8_t MyPriority;

static uint8_t seqArray[150]; //array containing random directions
static uint8_t arrayLength; //counter variable that contains length of array
static uint32_t score; //initial player score
static uint8_t seqIndex; //Sequence Index 
static uint8_t playtimeLeft; //Play time counter
static uint8_t roundNumber; //Round number

static SequenceState_t Current_State; //State Machine Current State Variable

static uint32_t adcResults[2];//Array for Joystick AD converter function
static uint8_t Last_Zval;//Last value for event checker
static uint32_t Neutral[2]; //Array containing neutral positions for X, Y
static uint8_t input;//variable to pass user input to OLED

/*------------------------------ Module Code ------------------------------*/

/****************************************************************************
 Function
     InitSequence
 Parameters
     uint8_t : the priorty of this service
 Returns
     bool, false if error in initialization, true otherwise
 Description
     Initialize Joystick pins and program, sets input for touch button and
     Z button.  Initializes Last_Zvar for event checking function xyVal
****************************************************************************/

bool InitSequence(uint8_t Priority)
{    
  ES_Event_t ThisEvent;

  MyPriority = Priority;
  //Initialize Framework Pins for Joystick
  //Pins RB2-Y, RB3-X are analog inputs, RA2-Z is digital Input,
  //Set Touch Sensor as Digital Input RB4-TS
  ANSELBbits.ANSB2 = 1;
  ANSELBbits.ANSB3 = 1;
  TRISBbits.TRISB2 = 1;
  TRISBbits.TRISB3 = 1;
  TRISAbits.TRISA2 = 1;
  TRISBbits.TRISB4 = 1;
  
  //Initialization of AD converter
  ADC_ConfigAutoScan((BIT4HI | BIT5HI), 2);
  
  //Initializing Last_Zval for event checker
  Last_Zval = PORTBbits.RB4;
  
  //Set current State
  Current_State = PseudoInit;
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
 PostSequence
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
   RunSequence
 Parameters
   ES_Event : the event to process
 Returns
   ES_Event, ES_NO_EVENT if no error ES_ERROR otherwise
 Description
     Initializes the game score, round, and array length. Obtains neutral values
 * for X and Y axis of joystick. Creates a random directions to display to
 * the user and later check against the user input. Post events to Game 
 * State Machine and the OLED State Machine. Updates the score and round values

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
        case PseudoInit:
        {
                if (ThisEvent.EventType == ES_INIT)
                {
                      // Read X and Y values from Joystick to obtain neutral positions
                      ADC_MultiRead(adcResults);
                      Neutral[0] = adcResults[0];           // Y neutral position
                      Neutral[1] = adcResults[1];           // X neutral position
                      printf("Yn %d\r\n", Neutral[0]);
                      printf("Xn %d\r\n", Neutral[1]);

                      ES_Event_t InitEvent;
                      InitEvent.EventType = ES_FIRST_ROUND;
                      PostSequence(InitEvent);
                      Current_State = SequenceCreate;
                }
        }
        break;
        
        case SequenceCreate:
        {
            switch (ThisEvent.EventType)
            {
                case ES_FIRST_ROUND:
                {   
                    // Initialize array length, round and score 
                    seqIndex = 0;
                    arrayLength = 4;
                    roundNumber = 1;
                    score = 0;

                    // Randomly initialize a sequence
                    for (i = 0; i < arrayLength; i++){
                        seqArray[i] = ES_Timer_GetTime() % 8;
                    }
                    
                    printf("sequence %d \r\n", seqArray[0]);
                    printf("sequence %d \r\n", seqArray[1]);
                    printf("sequence %d \r\n", seqArray[2]);
                    printf("sequence %d \r\n", seqArray[3]);
                }
                break;
                
                case ES_NEXT_ROUND:
                {
                    seqArray[arrayLength] = ES_Timer_GetTime() % 8;
                    arrayLength++;
                    roundNumber++;
                    seqIndex = 0;
                    
                    printf("sequence %d \r\n", seqArray[0]);
                    printf("sequence %d \r\n", seqArray[1]);
                    printf("sequence %d \r\n", seqArray[2]);
                    printf("sequence %d \r\n", seqArray[3]);
                    printf("sequence %d \r\n", seqArray[4]);
                }
                break;
                
                case ES_TIMEOUT: 
                {
                    if (ThisEvent.EventParam == READY_TIMER)
                    {
                        // Update display, start direction timer and change state
                        ES_Event_t DisplayEvent;
                        DisplayEvent.EventType = ES_DISPLAY_PLAY_INPUT;
                        DisplayEvent.EventParam = seqArray[seqIndex];
                        //PostDisplay(DisplayEvent);
                        seqIndex++;
                        ES_Timer_InitTimer(DIRECTION_TIMER, 500);
                        Current_State = SequenceDisplay;

                        printf("Direction %d \r\n", seqArray[seqIndex]); 
                    }
                }
                break;
                
                default:{} break;
            }
        }
        break;
        
        case SequenceDisplay:
        {
            switch(ThisEvent.EventType)
            {
                case ES_TIMEOUT:
                {
                    switch (ThisEvent.EventParam)
                    {
                        case DIRECTION_TIMER:
                        {
                            if (seqIndex < arrayLength){
                                ES_Event_t DisplayEvent;
                                DisplayEvent.EventType = ES_DISPLAY_PLAY_INPUT;
                                DisplayEvent.EventParam = seqArray[seqIndex];
                                //PostDisplay(DisplayEvent);
                                seqIndex++;
                                ES_Timer_InitTimer(DIRECTION_TIMER, 500);

                                // Last direction
                                if (seqIndex == arrayLength - 1){
                                    ES_Timer_InitTimer(LAST_DIRECTION_TIMER, 500);
                                    seqIndex = 0;
                                }

                                printf("Direction %d \r\n", seqArray[seqIndex]);    
                            }
                        }
                        break;
                        
                        case GO_TIMER:
                        {
                            playtimeLeft = ROUND_TIME;
                            // Update display, start input timer 
                            ES_Event_t DisplayEvent;
                            DisplayEvent.EventType = ES_DISPLAY_PLAY;
                            DisplayEvent.EventType = playtimeLeft;              // depends on how Ashley implements display service
                            //PostDisplay(DisplayEvent);
                            ES_Timer_InitTimer(INPUT_TIMER, 1000);
                            Current_State = SequenceInput;

                            printf("GAMEPLAY SCREEN\r\n");
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
                    if (ThisEvent.EventParam == INPUT_TIMER)
                    {
                        if (playtimeLeft > 0) 
                        {
                            // Inform display service to update time
                            playtimeLeft--;
                            ES_Event_t DisplayEvent;
                            DisplayEvent.EventType = ES_DISPLAY_PLAY;
                            DisplayEvent.EventType = playtimeLeft;
                            ES_Timer_InitTimer(INPUT_TIMER, 1000);

                            printf("%u seconds remaining", playtimeLeft);
                        } 

                        else if (playtimeLeft == 0) 
                        {
                            // Update sequence state machine
                            CurrentState = SequenceCreate;
                            ES_Event_t SequenceEvent;                            
                            SequenceEvent.EventType = ES_FIRST_ROUND;
                            PostSequence(SequenceEvent);

                            // Inform GameState machine 
                            ES_Event_t GameStateEvent;
                            GameStateEvent.EventType = ES_GAME_COMPLETE;
                            PostGameState(GameStateEvent);

                            // Inform display service
                            ES_Event_t DisplayEvent;
                            DisplayEvent.EventType = ES_DISPLAY_GAMECOMPLETE;
                            //PostDisplay(DisplayEvent);

                            printf("Game Over from Timeout");
                        }
                    }
                    
                }
                break;

                case ES_INCORRECT_INPUT:
                {
                    // Update sequence state machine
                    CurrentState = SequenceCreate;
                    ES_Event_t SequenceEvent;                            
                    SequenceEvent.EventType = ES_FIRST_ROUND;
                    PostSequence(SequenceEvent);

                    // Inform GameState machine 
                    ES_Event_t GameStateEvent;
                    GameStateEvent.EventType = ES_GAME_COMPLETE;
                    PostGameState(GameStateEvent);

                    // Inform display service
                    ES_Event_t DisplayEvent;
                    DisplayEvent.EventType = ES_DISPLAY_GAMECOMPLETE;
                    //PostDisplay(DisplayEvent);

                    printf("Game Over from Incorrect Input");
                }
                break;
                
                case ES_CORRECT_INPUT_FINAL://this is sent from the event checker
                {
                    //Post to OLED to transition to Round Complete
                    //Post to myself to transition
                    ThisEvent.EventType = ES_NEXT_ROUND;
                    PostSequence(ThisEvent);

                    //Increment Score
                    if (arrayLength <= 4)
                    {
                        score = score + 10;
                    }
                    else
                    {
                        score = score + (arrayLength / 4) * 10;
                    }
                    
                    //Update Current State
                    Current_State = SequenceCreate;
                    
                    printf("input round won\r\n");
                }
                break;
                
                case ES_CORRECT_INPUT://this is sent from the event checker
                {
                    //Increment Score
                    if (arrayLength <= 4)
                    {
                        score = score + 10;
                    }
                    else
                    {
                        score = score + (arrayLength / 4) * 10;
                    }
                    //Post to OLED to display correct input
                    
                    //Increment Sequence Index
                    seqIndex++; //This sequence index begins at zero
                    
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
 * This event checker takes a read of the joystick x and y values when
 * the z button is pressed, preserving the input the user wants to give to
 * the game.
 ----------------------------------------------------------------------------*/
bool xyVal (void)
{
    //Return Variable Declaration and initialization
    static bool returnValue = false;
    //Variable declaration for Z button value
    static uint8_t Current_Zval;
    //Variable declaration for event
    ES_Event_t ThisEvent;
    
    /*-----------------------------------------------------------------------
     This If statement minimizes the amount of times this event checking
     function gets call, to not bug down processing time-------------------*/
    if ((Current_State == SequenceInput) && (seqIndex <= (arrayLength - 1)))
    {
        //Read Current Z value
        Current_Zval = PORTBbits.RB4;
        
        //Decision Matrix for executable action
        if (Current_Zval == Last_Zval)
        {
            //Do nothing; user has not decided on input if both are zero
            //or user has not released Z button
            
            returnValue = true;
        }
        else if (Current_Zval == 1 && Last_Zval == 0)
        {
            //Read X and Y values from Joystick
            ADC_MultiRead(adcResults);
            //set Last_Zval to Current_Zval
            //This will help us to post an event after the user 
            Last_Zval = Current_Zval;
            
            returnValue = true;
        }
        else if (Last_Zval == 1 && Current_Zval == 0)
        {
            //Return Last_Zval to zero
            Last_Zval = Current_Zval;
            printf("ADC %d     ",adcResults[0]);
            printf("ADC %d     \r\n",adcResults[1]);
            //Perform Calculations to check if the input was a correct input
            //or an incorrect input and then post to myself
            
            //Check if this is the last input to post correct event
            if (seqIndex < (arrayLength - 1))          // Not last input
            {
                printf("seqIndex %d\r\n",seqIndex);
                if(Input_Check(adcResults) == true)
                {
                    //Post Correct event
                    ThisEvent.EventType = ES_CORRECT_INPUT;
                    PostSequence(ThisEvent);
                    printf("posted Correct Input\r\n");
                }
                else
                {
                    //Post Incorrect event
                    ThisEvent.EventType = ES_INCORRECT_INPUT;
                    PostSequence(ThisEvent);
                    printf("posted Incorrect Input\r\n");
                }
            }
            else if (seqIndex == (arrayLength - 1))    // Last input
            {
                printf("seqIndex2 %d\r\n",seqIndex);
                if(Input_Check(adcResults) == true)
                {
                    //Post Correct final event
                    ThisEvent.EventType = ES_CORRECT_INPUT_FINAL;
                    PostSequence(ThisEvent);
                    printf("posted Correct Input F\r\n");
                }
                else
                {
                    //Post Incorrect event
                    ThisEvent.EventType = ES_INCORRECT_INPUT;
                    PostSequence(ThisEvent);
                    printf("posted Incorrect Input\r\n");
                }
            }
            
            returnValue = true;
        }
        
    }
    return returnValue;
}

/*---------------------------------------------------------------------------
 This function compares the input of the X, Y axis of joystick and compares
 that input to the sequence of directions, being currently analyzed
 Also updates the input variable to display to the oled---------------------*/
bool Input_Check(uint32_t *adcResults)
{
    //Return Val Declaration and initialization
    static bool returnValue = false;
    //Direction being analyzed
    switch (seqArray[seqIndex])
    {
        case 0:
        {
            if ((adcResults[1] > 1) && (adcResults[1] < (Neutral[1] - 10)) && 
                    (adcResults[0] >= (Neutral[0] - 20)) && 
                    (adcResults[0] <= (Neutral[0] + 20)))
            {
                input = 0;
                returnValue = true;
            }
        }
        break;
        
        case 1:
        {
            if ((adcResults[1] <= 1) && 
                    (adcResults[0] >= (Neutral[0] - 20)) && 
                    (adcResults[0] <= (Neutral[0] + 20)))
            {
                input =1;
                returnValue = true;
            }
        }
        break;
        
        case 2:
        {
            if ((adcResults[1] > (Neutral[1] + 10)) && 
                    (adcResults[1] < 1020) && 
                    (adcResults[0] >= (Neutral[0] - 20)) && 
                    (adcResults[0] <= (Neutral[0] + 20)))
            {
                input = 2;
                returnValue = true;
            }
        }
        break;
        
        case 3:
        {
            if ((adcResults[1] >= 1020) && 
                    (adcResults[0] >= (Neutral[0] - 20)) && 
                    (adcResults[0]<=(Neutral[0] + 20)))
            {
                input = 3;
                returnValue = true;
            }
        }
        break;
        
        case 4:
        {
            if ((adcResults[0] > 1) && 
                    (adcResults[0] < (Neutral[0] - 10)) && 
                    (adcResults[1] >= (Neutral[1] - 20)) && 
                    (adcResults[1] <= (Neutral[1] + 20)))
            {
                input = 4;
                returnValue = true;
            }
        }
        break;
        
        case 5:
        {
            if ((adcResults[0] <= 1) && 
                    (adcResults[1] >= (Neutral[1] - 20)) && 
                    (adcResults[1] <= (Neutral[1] + 20)))
            {
                input = 5;
                returnValue = true;
            }
        }
        break;
        
        case 6:
        {
            if ((adcResults[0] > (Neutral[0] + 10)) && 
                    (adcResults[0] < 1020) && 
                    (adcResults[1] >= (Neutral[1] - 20)) && 
                    (adcResults[1] <= (Neutral[1] + 20)))
            {
                input = 6;
                returnValue = true;
            }
        }
        break;
        
        case 7:
        {
            if ((adcResults[0] >= 1020) && 
                    (adcResults[1] >= (Neutral[1] - 20)) && 
                    (adcResults[1] <= (Neutral[1] + 20)))
            {
                input = 7;
                returnValue = true;
            }
        }
        break;
        
        default:{returnValue = false;}break;
        
    }
    return returnValue;
    
}
    