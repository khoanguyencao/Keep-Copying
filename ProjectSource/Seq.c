/*******************************************
 * Note: Currently missing a way to inform display
 * of input direction
 * 
*******************************************/

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
#include "Display.h"
#include "hal.h"

/*----------------------------- Module Defines ----------------------------*/

#define ROUND_TIME 15
/*---------------------------- Module Functions ---------------------------*/
/* prototypes for private functions for this machine.They should be functions
   relevant to the behavior of this state machine
*/
static void updateScore();
static bool inputChecker(uint32_t *adcResults);
static uint16_t bitPack(uint8_t score, uint8_t time, uint8_t input);

/*---------------------------- Module Variables ---------------------------*/
// with the introduction of Gen2, we need a module level Priority variable
static uint8_t MyPriority;

static uint8_t seqArray[150]; //array containing random directions
static uint8_t arrayLength; //counter variable that contains length of array
static uint8_t score; //initial player score
static uint8_t seqIndex; //Sequence Index 
static uint8_t playtimeLeft; //Play time counter
static uint8_t roundNumber; //Round number
static uint8_t displayCounter;

static SequenceState_t CurrentState; //State Machine Current State Variable

static uint32_t adcResults[2]; //Array for Joystick AD converter function
static uint8_t lastTouchSensor; //Last value for event checker
static uint32_t Neutral[2]; //Array containing neutral positions for X, Y
static uint8_t input; //variable to pass user input to OLED

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
     Z button.  Initializes lastTouchSensor for event checking function xyVal
****************************************************************************/

bool InitSequence(uint8_t Priority)
{    
  ES_Event_t InitEvent;
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
  
  //Initializing lastTouchSensor for event checker
  lastTouchSensor = PORTBbits.RB4;
  
  //Set current State
  CurrentState = PseudoInit;
  // post the initial transition event
  InitEvent.EventType = ES_INIT;
  if (ES_PostToService(MyPriority, InitEvent) == true)
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
    switch(CurrentState)
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

                      //ES_Event_t InitEvent;
                      //InitEvent.EventType = ES_FIRST_ROUND;
                      //PostSequence(InitEvent);
                      CurrentState = SequenceCreate;
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
                    srand(ES_Timer_GetTime());
                    for (uint8_t i = 0; i < arrayLength; i++){
                        //uint16_t time = rand();
                        seqArray[i] = (rand() % 80) / 10; //time % 8;
                        printf("%u\r\n", seqArray[i]);
                    }
                }
                break;
                
                case ES_NEXT_ROUND:
                {
                    // Append random direction to sequence
                    seqIndex = 0;
                    seqArray[arrayLength] = (rand() %80)/10;        //ES_Timer_GetTime() % 8;
                    arrayLength++;
                    roundNumber++;
                    
                    // TESTING
                    //printf("sequence %d \r\n", seqArray[0]);
                    //printf("sequence %d \r\n", seqArray[1]);
                    //printf("sequence %d \r\n", seqArray[2]);
                    //printf("sequence %d \r\n", seqArray[3]);
                    //printf("sequence %d \r\n", seqArray[4]);
                }
                break;
                
                case ES_TIMEOUT: 
                {
                    if (ThisEvent.EventParam == READY_TIMER)
                    {
                        // Inform display service to demonstrate input and starts first direction timer
                        displayCounter = 0;
                        ES_Event_t DisplayEvent;
                        DisplayEvent.EventType = ES_DISPLAY_INSTRUCTION;
                        DisplayEvent.EventParam = seqArray[displayCounter];
                        PostDisplay(DisplayEvent);
                        displayCounter++;
                        ES_Timer_InitTimer(DIRECTION_TIMER, 500);
                        CurrentState = SequenceDisplay;

                        // TESTING
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
                            // Inform display service to demonstrate input and starts subsequent direction timers
                            ES_Event_t DisplayEvent;
                            DisplayEvent.EventType = ES_DISPLAY_INSTRUCTION;
                            DisplayEvent.EventParam = seqArray[displayCounter];
                            PostDisplay(DisplayEvent);
                            printf("Direction %d \r\n", seqArray[displayCounter]);
                                                        
                            // If not last direction
                            if (displayCounter < (arrayLength - 1)){
                                ES_Timer_InitTimer(DIRECTION_TIMER, 500);
                            }

                            // If last direction
                            if (displayCounter == (arrayLength - 1)){
                                ES_Timer_InitTimer(LAST_DIRECTION_TIMER, 500);
                            }
                            displayCounter++;
                        }
                        break;
                        
                        case GO_TIMER:
                        {
                            playtimeLeft = ROUND_TIME;
                            // Inform display service to update to play screen and starts input timer
                            ES_Event_t DisplayEvent;
                            input = 8;
                            DisplayEvent.EventType = ES_DISPLAY_PLAY_UPDATE;
                            DisplayEvent.EventParam = bitPack(score, playtimeLeft, input);
                            PostDisplay(DisplayEvent);
                            ES_Timer_InitTimer(INPUT_TIMER, 1000);
                            CurrentState = SequenceInput;

                            // TESTING
                            printf("Gameplay Screen\r\n");
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
                            DisplayEvent.EventType = ES_DISPLAY_PLAY_UPDATE;
                            DisplayEvent.EventParam = bitPack(score, playtimeLeft, input);
                            PostDisplay(DisplayEvent);
                            ES_Timer_InitTimer(INPUT_TIMER, 1000);

                            printf("%u seconds remaining\r\n", playtimeLeft);
                        } 

                        else if (playtimeLeft == 0) 
                        {
                            // Update sequence state machine
                            CurrentState = SequenceCreate;

                            // Inform GameState machine 
                            ES_Event_t GameStateEvent;
                            GameStateEvent.EventType = ES_GAME_COMPLETE;
                            GameStateEvent.EventParam = score;
                            PostGameState(GameStateEvent);

                            printf("Game Over from Timeout\r\n");
                        }
                    }
                    
                }
                break;

                case ES_INCORRECT_INPUT:
                {
                    // Update sequence state machine
                    CurrentState = SequenceCreate;

                    // Inform GameState machine 
                    ES_Event_t GameStateEvent;
                    GameStateEvent.EventType = ES_GAME_COMPLETE;
                    GameStateEvent.EventParam = score;
                    PostGameState(GameStateEvent);

                    printf("Game Over from Incorrect Input\r\n");
                }
                break;

                case ES_CORRECT_INPUT:
                {
                    updateScore();
                    seqIndex++;

                    ES_Event_t DisplayEvent;
                    DisplayEvent.EventType = ES_DISPLAY_PLAY_UPDATE;
                    DisplayEvent.EventParam = bitPack(score, playtimeLeft, input);
                    PostDisplay(DisplayEvent);
                    
                    // TESTING
                    //printf("Input Correct\r\n");
                }
                break;
                
                case ES_CORRECT_INPUT_FINAL:
                {
                    updateScore();
                    
                    // Inform Display service
                    ES_Event_t DisplayEvent;
                    DisplayEvent.EventType = ES_DISPLAY_PLAY_UPDATE;
                    DisplayEvent.EventParam = bitPack(score, playtimeLeft, input);
                    PostDisplay(DisplayEvent);
                    
                    // Update sequence state machine
                    CurrentState = SequenceCreate;
                    ES_Event_t SequenceEvent;                            
                    SequenceEvent.EventType = ES_NEXT_ROUND;
                    PostSequence(SequenceEvent);

                    // Inform GameState machine 
                    ES_Event_t GameStateEvent;
                    GameStateEvent.EventType = ES_ROUND_COMPLETE;
                    PostGameState(GameStateEvent);

                    // TESTING
                    //printf("Round Complete\r\n");
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

/* Event Checkers ------------------------------------------------------------
 * This event checker takes reads the joystick x and y values when
 * the z button is pressed, preserving the input the user wants to give to
 * the game.
 ----------------------------------------------------------------------------*/
bool CheckXYVal (void)
{
    static bool returnValue = false;
    static uint8_t currentTouchSensor;

    // Only checks during the SequenceInput state   
    if ((CurrentState == SequenceInput) && (seqIndex <= (arrayLength - 1)))
    {
        ES_Event_t JoystickEvent;
        // Read Current Z value
        currentTouchSensor = PORTBbits.RB4;
        
        // Decision Matrix for executable action
        if (currentTouchSensor == lastTouchSensor)
        {
            // Do nothing; user has not decided on input if both are zero
            // or user has not released Z button
            
            returnValue = true;
        }
        else if (currentTouchSensor == 1 && lastTouchSensor == 0)
        {
            // Read X and Y values from Joystick
            ADC_MultiRead(adcResults);
            lastTouchSensor = currentTouchSensor;
            returnValue = true;
        }
        else if (lastTouchSensor == 1 && currentTouchSensor == 0)
        {
            printf("ADC %d     ", adcResults[0]);
            printf("ADC %d     \r\n", adcResults[1]);
            
            // Check if this is the last input to post correct event
            if (seqIndex < (arrayLength - 1))          // Not last input
            {
                //printf("seqIndex %d\r\n",seqIndex);
                if (inputChecker(adcResults) == true)
                {
                    // Post Correct Event
                    JoystickEvent.EventType = ES_CORRECT_INPUT;
                    PostSequence(JoystickEvent);
                    //printf("posted Correct Input\r\n");
                }
                else
                {
                    // Post Incorrect Event
                    JoystickEvent.EventType = ES_INCORRECT_INPUT;
                    PostSequence(JoystickEvent);
                    //printf("posted Incorrect Input\r\n");
                }
            }
            else if (seqIndex == (arrayLength - 1))    // Last input
            {
                //printf("seqIndex2 %d\r\n",seqIndex);
                if (inputChecker(adcResults) == true)
                {
                    //Post Correct Final Event
                    JoystickEvent.EventType = ES_CORRECT_INPUT_FINAL;
                    PostSequence(JoystickEvent);
                    //printf("posted Correct Input F\r\n");
                }
                else
                {
                    //Post Incorrect Event
                    JoystickEvent.EventType = ES_INCORRECT_INPUT;
                    PostSequence(JoystickEvent);
                    //printf("posted Incorrect Input\r\n");
                }
            }
            lastTouchSensor = currentTouchSensor;
            returnValue = true;
        }
    }
    return returnValue;
}

/*---------------------------------------------------------------------------
 This function compares the input of the X, Y axis of joystick and compares
 that input to the sequence of directions, being currently analyzed
 Also updates the input variable to display to the oled---------------------*/
static bool inputChecker(uint32_t *adcResults)
{
    static bool returnValue = false;
    // Switch case to analyze direction 
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
           else
           {
                returnValue = false;
           }
        }
        break;
        
        case 1:
        {
            if ((adcResults[1] <= 1) && 
                    (adcResults[0] >= (Neutral[0] - 20)) && 
                    (adcResults[0] <= (Neutral[0] + 20)))
            {
                input = 1;
                returnValue = true;
            }
           else
           {
                returnValue = false;
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
           else
           {
                returnValue = false;
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
           else
           {
                returnValue = false;
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
           else
           {
                returnValue = false;
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
           else
           {
                returnValue = false;
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
           else
           {
                returnValue = false;
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
           else
           {
                returnValue = false;
           }
        }
        break;
        
        default:{} break;
        
    }
    return returnValue;
    
}

static void updateScore(){
    if (arrayLength <= 4) {
        score = score + 1;
    } else {
        score = score + (arrayLength / 4) * 1;
    }
}

// score 8 bits, time 4 bits, input 4 bits 
static uint16_t bitPack(uint8_t score, uint8_t time, uint8_t input){
    uint16_t EventParam = score << 8;
    EventParam = EventParam | (time << 4);
    EventParam = EventParam | (input);
    return EventParam;
}

