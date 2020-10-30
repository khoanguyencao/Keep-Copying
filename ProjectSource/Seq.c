#include "Seq.h"
#include "PIC32_AD_Lib.h"
#include "GameState.h"
//Hardware
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
static uint8_t *ps_array = seq_array; //pointer to seq_array
static uint8_t array_len=4; //counter variable that contains length of array
static uint32_t score=0; //initial player score
static uint8_t seq_idx=0; //Sequence Index 
static uint8_t play_time = 0; //Play time counter
static uint8_t round = 1; //Round number
static uint8_t display_c=1; // Display counter, for demonstrating sequence

static SState_t Current_State; //State Machine Current State Variable

static uint32_t adcResults[2];//Array for Joystick AD converter function
static uint8_t Last_Zval;//Last value for event checker
static uint32_t Neutral[2]; //Array containing neutral positions for X, Y
static uint8_t input=8;//variable to pass user input to OLED

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
  ADC_ConfigAutoScan( (BIT4HI | BIT5HI), 2);
  
  //Initializing Last_Zval for event checker
  //Last_Zval=PORTAbits.RA2;
  Last_Zval=PORTBbits.RB4;
  
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
                      //Read X and Y values from Joystick to obtain neutral positions
                      ADC_MultiRead(adcResults);
                      Neutral[0]=adcResults[0];//Y neutral position
                      Neutral[1]=adcResults[1];//X neutral position
                      printf("Yn %d\r\n",Neutral[0]);
                      printf("Xn %d\r\n",Neutral[1]);
                      
                      //Initializing complete, proceed to next state
                      //game machine will post to sequence  
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
                  
                    //Counter variable
                    static uint8_t i;
                    
                    //Clear Array
                    for(i=0;i<150;i++)
                    {
                        *(ps_array+i)=0;
                    }
                    
                    //Init Array length, round, and score 
                    array_len =4;
                    score=0;
                    round = 1;
                    
                    srand(ES_Timer_GetTime());
                    //Sequence Random initialization
                    for(i=0;i<array_len;i++)
                    {
                        
                        seq_array[i]=(rand() %80)/10; //populate new array element
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
                    seq_array[array_len]=(rand() % 8); //populate new array element
                    array_len++; //Increment Array size
                    round++; //Increment Round number
                    
                    seq_idx=0; //reset sequence index
                    
                    printf("sequence %d \r\n",seq_array[0]);
                    printf("sequence %d \r\n",seq_array[1]);
                    printf("sequence %d \r\n",seq_array[2]);
                    printf("sequence %d \r\n",seq_array[3]);
                    printf("sequence %d \r\n",seq_array[4]);
                    
                    
                }
                break;
                
                case ES_TIMEOUT: 
                //Ensure that a timer from INPUT TIMER doesn't interfere
                //This TimeOut comes from READY_TIMER
                {
                    if(ThisEvent.EventParam == READY_TIMER)
                    {
                        printf("Direction %d \r\n", seq_array[0]); 
                        //here goes the posting to oled to display first dir

                        //Initialize timer for displaying sequence, This timer
                        //Posts to myself to continue displaying sequence
                        ES_Timer_InitTimer(DIRECTION_TIMER, 500);
                        Current_State=SequenceDisplay; //Transition to Seq_Display
                    }
                }
                break;
                
                default:{} break;
            }
        }
        break;
        
        case SequenceDisplay:
        {
            //display_c is counter to count the sequence of directions that
            //have been displayed to the user, and begin a transition to 
            //the GO screen
            
            switch(ThisEvent.EventType)
            {
                case ES_TIMEOUT:
                {
                    //This part deals with the TimeOut event from GO Screen
                    switch (ThisEvent.EventParam)
                    {
                        case DIRECTION_TIMER:
                        {
                            if(display_c < (array_len-1))
                            {
                                printf("Direction %d \r\n", seq_array[display_c]); 
                                //here goes the posting to oled to display
                                //subsequent directions

                                //Initialize timer for displaying sequence, This timer
                                //Posts to myself to continue displaying sequence
                                ES_Timer_InitTimer(DIRECTION_TIMER, 500);

                                //Increase counter
                                display_c++;
                            }
                            else if (display_c == (array_len-1))
                            {
                                printf("Direction %d \r\n", seq_array[display_c]); 
                                //here goes the posting to oled, display last dir

                                /*----------------------------------------------------
                                 * Initialize timer for displaying sequence, This timer
                                 * post to Game SM to proceed to GO screen
                                 * --------------------------------------------------*/
                                ES_Timer_InitTimer(LAST_DIRECTION_TIMER, 500);
                                //Notice that is a different Timer that

                                //Reset Display Counter
                                display_c = 1;
                            }
                        }
                        break;
                        
                        case GO_TIMER://Received from GAME SM
                        {
                            //Post to OLED to display gameplay screen
                            //Remember to ES_Event_t ThisEvent.EventType...
                            
                            printf("GAMEPLAY SCREEN\r\n");
                            //Transition to next State
                            Current_State = SequenceInput;
                            //Start 1 s Input Timer
                            ES_Timer_InitTimer(INPUT_TIMER, 1000);
                            ES_Timer_InitTimer(INSTRUCTION_TIMER, 101);
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
                //keeps track of playtime 
                case ES_TIMEOUT:
                {
                    if (ThisEvent.EventParam == INPUT_TIMER)
                    {
                        if (play_time < 14)
                        {
                            //Restart Timer
                            ES_Timer_InitTimer(INPUT_TIMER, 1000);

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
                            //Send event to OLED for Game Over
                            printf("timeout gameover\r\n");
                            ThisEvent.EventType = ES_GAME_COMPLETE;
                            PostGameState(ThisEvent);
                        }  
                    }
                    /*--------------------------------------------------------
                     This timer is set such that the user has a visual 
                     representation of the joystick on the OLED before 
                     making the input selection -----------------------------*/
                    if (ThisEvent.EventParam == INSTRUCTION_TIMER)
                    {
                        //Read X and Y values from Joystick
                        ADC_MultiRead(adcResults);
                        //Obtain direction from user input
                        Input_Direction(adcResults);
                        //Post to OLED
                        printf("input  %d\r\n",input);
                        //Restart Timer
                        ES_Timer_InitTimer(INSTRUCTION_TIMER, 101);
                    }
                }
                break;

                case ES_INCORRECT_INPUT://sent from event checker
                {
                    //Post to OLED to transition to game over
                    //Update Current State
                    Current_State = SequenceCreate;
                    
                    printf("input gameover\r\n");
                    ThisEvent.EventType = ES_GAME_COMPLETE;
                    PostGameState(ThisEvent);
                }
                break;
                
                case ES_CORRECT_INPUT_F://this is sent from the event checker
                {
                    //Post to OLED to transition to Round Complete
                    
                    //Post to myself to transition
                    ThisEvent.EventType = ES_NEXT_ROUND;
                    PostSequence(ThisEvent);
                    ThisEvent.EventType = ES_ROUND_COMPLETE;
                    PostGameState(ThisEvent);

                    //Increment Score
                    if (array_len<=4)
                    {
                        score=score+10;
                    }
                    else
                    {
                        score=score+(array_len/4)*10;
                    }
                    
                    //Update Current State
                    Current_State = SequenceCreate;
                    
                    printf("input round won\r\n");
                }
                break;
                
                case ES_CORRECT_INPUT://this is sent from the event checker
                {
                    //Increment Score
                    if (array_len<=4)
                    {
                        score=score+10;
                    }
                    else
                    {
                        score=score+(array_len/4)*10;
                    }

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
 * This event checker takes a read of the joystick x and y values when
 * the z button is pressed, preserving the input the user wants to give to
 * the game.
 ----------------------------------------------------------------------------*/
bool xyVal (void)
{
    //Return Variable Declaration and initialization
    static bool Ret_Val = false;
    //Variable declaration for Z button value
    static uint8_t Current_Zval;
    //Variable declaration for event
    static ES_Event_t ThisEvent;
    
    /*-----------------------------------------------------------------------
     This If statement minimizes the amount of times this event checking
     function gets call, to not bug down processing time-------------------*/

    if ((Current_State == SequenceInput) && (seq_idx <= (array_len-1)))
    {

        //Read Current Z value
        //Current_Zval = PORTAbits.RA2;
        Current_Zval = PORTBbits.RB4;
               //zzzzzzz printf("here\r\n");
        //Decision Matrix for executable action
        if (Current_Zval == Last_Zval)
        {
            //Do nothing; user has not decided on input if both are zero
            //or user has not released Z button
            
            Ret_Val=true;
        }
        else if (Current_Zval == 1 && Last_Zval == 0)
        {
            //Read X and Y values from Joystick
            ADC_MultiRead(adcResults);
            //set Last_Zval to Current_Zval
            //This will help us to post an event after the user 
            Last_Zval = Current_Zval;
            
            Ret_Val=true;
        }
        else if (Last_Zval == 1 && Current_Zval ==0)
        {

            //Return Last_Zval to zero
            Last_Zval = Current_Zval;
            printf("ADC %d     ",adcResults[0]);
            printf("ADC %d     \r\n",adcResults[1]);
            //Perform Calculations to check if the input was a correct input
            //or an incorrect input and then post to myself
            
            //Check if this is the last input to post correct event
            if (seq_idx < (array_len-1)) //Not last input
            {
                printf("seq_idx %d\r\n",seq_idx);
                if(Input_Check(adcResults) == true)
                {
                    //Post Correct event
                    ThisEvent.EventType = ES_CORRECT_INPUT;
                    PostSequence(ThisEvent);
                    printf("posted Correct Input\r\n");
                    printf("input %d\r\n",input);
                }
                else
                {
                    //Post Incorrect event
                    ThisEvent.EventType = ES_INCORRECT_INPUT;
                    PostSequence(ThisEvent);
                    printf("posted Incorrect Input\r\n");
                }
            }
            else if (seq_idx == (array_len-1)) // Last input
            {
                printf("seq_idx2 %d\r\n",seq_idx);
                if(Input_Check(adcResults) == true)
                {
                    //Post Correct final event
                    ThisEvent.EventType = ES_CORRECT_INPUT_F;
                    PostSequence(ThisEvent);
                    printf("posted Correct Input F\r\n");
                    printf("input %d\r\n",input);
                }
                else
                {
                    //Post Incorrect event
                    ThisEvent.EventType = ES_INCORRECT_INPUT;
                    PostSequence(ThisEvent);
                    printf("posted Incorrect Input\r\n");
                }
            }
            
            Ret_Val=true;
        }        
    }
    else if (Current_State == SequenceCreate)
    {
        //Read Current Z value
        //Current_Zval = PORTAbits.RA2;
        Current_Zval = PORTBbits.RB4;

        //Decision Matrix for executable action
        if (Current_Zval == Last_Zval)
        {
            //Do nothing; user has not decided on input if both are zero
            //or user has not released Z button

            Ret_Val=true;
        }
        else if (Current_Zval == 1 && Last_Zval == 0)
        {

            Last_Zval = Current_Zval;

            Ret_Val=true;
        }
        else if (Last_Zval == 1 && Current_Zval ==0)
        {
            Last_Zval = Current_Zval;
            ThisEvent.EventType = ES_SENSOR_PRESSED;
            PostGameState(ThisEvent);
            Ret_Val=true;
        }  
    }
    return Ret_Val;
}

/*---------------------------------------------------------------------------
 This function compares the input of the X, Y axis of joystick and compares
 that input to the sequence of directions, being currently analyzed
 Also updates the input variable to display to the oled---------------------*/
bool Input_Check(uint32_t *adcResults)
{
    //Return Val Declaration and initialization
    static bool Ret_Val = false;
    //Direction being analyzed
    switch (seq_array[seq_idx])
    {
        printf("seq array %d",seq_array[seq_idx]);
        case 0:
        {
            if(adcResults[1] >1 && adcResults[1] <(Neutral[1]-2) && adcResults[0]>=(Neutral[0]-20) && adcResults[0]<=(Neutral[0]+20))
            {
                input = 0;
                Ret_Val = true;
            }
            else
            {
                Ret_Val = false;
            }
        }
        break;
        
        case 1:
        {
            if(adcResults[1] <=1 && adcResults[0]>=(Neutral[0]-20) && adcResults[0]<=(Neutral[0]+20))
            {
                input =1;
                Ret_Val = true;
            }
            else
            {
                Ret_Val = false;
            }
        }
        break;
        
        case 2:
        {
            if(adcResults[1] >(Neutral[1]+2) && adcResults[1] <1020 && adcResults[0]>=(Neutral[0]-20) && adcResults[0]<=(Neutral[0]+20))
            {
                input = 2;
                Ret_Val = true;
            }
            else
            {
                Ret_Val = false;
            }
        }
        break;
        
        case 3:
        {
            if(adcResults[1] >=1020 && adcResults[0]>=(Neutral[0]-20) && adcResults[0]<=(Neutral[0]+20))
            {
                input = 3;
                Ret_Val = true;
            }
            else
            {
                Ret_Val = false;
            }
        }
        break;
        
        case 4:
        {
            if(adcResults[0] >1 && adcResults[0] <(Neutral[0]-2) && adcResults[1]>=(Neutral[1]-20) && adcResults[1]<=(Neutral[1]+20))
            {
                input = 4;
                Ret_Val = true;
            }
            else
            {
                Ret_Val = false;
            }
        }
        break;
        
        case 5:
        {
            if(adcResults[0] <=1 && adcResults[1]>=(Neutral[1]-20) && adcResults[1]<=(Neutral[1]+20))
            {
                input = 5;
                Ret_Val = true;
            }
            else
            {
                Ret_Val = false;
            }
        }
        break;
        
        case 6:
        {
            if(adcResults[0] >(Neutral[0]+2) && adcResults[0] <1020 && adcResults[1]>=(Neutral[1]-20) && adcResults[1]<=(Neutral[1]+20))
            {
                input = 6;
                Ret_Val = true;
            }
            else
            {
                Ret_Val = false;
            }
        }
        break;
        
        case 7:
        {
            if(adcResults[0] >=1020 && adcResults[1]>=(Neutral[1]-20) && adcResults[1]<=(Neutral[1]+20))
            {
                input = 7;
                Ret_Val = true;
            }
            else
            {
                Ret_Val = false;
            }
        }
        break;
        
        default:
        {
            Ret_Val=false;
        }break;
        
    }
    return Ret_Val;
    
}
    
uint8_t Input_Direction(uint32_t *adcResults)
{
    //Direction being analyzed
            if(adcResults[1] >1 && adcResults[1] <(Neutral[1]-2) && adcResults[0]>=(Neutral[0]-20) && adcResults[0]<=(Neutral[0]+20))
            {
                input = 0;
            }
            else if(adcResults[1] <=1 && adcResults[0]>=(Neutral[0]-20) && adcResults[0]<=(Neutral[0]+20))
            {
                input =1;
            }
            else if(adcResults[1] >(Neutral[1]+2) && adcResults[1] <1020 && adcResults[0]>=(Neutral[0]-20) && adcResults[0]<=(Neutral[0]+20))
            {
                input = 2;
            }
            else if(adcResults[1] >=1020 && adcResults[0]>=(Neutral[0]-20) && adcResults[0]<=(Neutral[0]+20))
            {
                input = 3;
            }
            else if(adcResults[0] >1 && adcResults[0] <(Neutral[0]-2) && adcResults[1]>=(Neutral[1]-20) && adcResults[1]<=(Neutral[1]+20))
            {
                input = 4;
            }
            else if(adcResults[0] <=1 && adcResults[1]>=(Neutral[1]-20) && adcResults[1]<=(Neutral[1]+20))
            {
                input = 5;
            }
            else if(adcResults[0] >(Neutral[0]+2) && adcResults[0] <1020 && adcResults[1]>=(Neutral[1]-20) && adcResults[1]<=(Neutral[1]+20))
            {
                input = 6;
            }
            else if(adcResults[0] >=1020 && adcResults[1]>=(Neutral[1]-20) && adcResults[1]<=(Neutral[1]+20))
            {
                input = 7;
            }
            else
            {
                input = 8;
            }

    return input;
    
}