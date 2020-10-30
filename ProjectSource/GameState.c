/****************************************************************************
 Module
   GameState.c

 Revision
   1.0.0

 Description
   GameState is an FSM that describes the current game state of the game.

 Notes

 History
 When           Who     What/Why
 -------------- ---     --------
 10/28/20       kcao    File creation 
****************************************************************************/
/*----------------------------- Include Files -----------------------------*/
/* include header files for this state machine as well as any machines at the
   next lower level in the hierarchy that are sub-machines to this machine
*/
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "GameState.h"

/*----------------------------- Module Defines ----------------------------*/

#define SENSOR_INPUT_PIN 10 // corresponds to real pin 11 for touch sensor

/*---------------------------- Module Functions ---------------------------*/
/* prototypes for private functions for this machine.They should be functions
   relevant to the behavior of this state machine
*/

/*---------------------------- Module Variables ---------------------------*/
// everybody needs a state variable, you may need others as well.
// type of state variable should match htat of enum in header file
static GameState_t CurrentState;
static uint16_t highScores[3];
static uint16_t roundNumber;

// with the introduction of Gen2, we need a module level Priority var as well
static uint8_t MyPriority;

/*------------------------------ Module Code ------------------------------*/
/****************************************************************************
 Function
     InitGameState

 Parameters
     uint8_t : the priorty of this service

 Returns
     bool, false if error in initialization, true otherwise

 Description
     Saves away the priority, sets up the initial transition and does any
     other required initialization for this state machine
 Notes

 Author
  K Cao, 10/28/20
****************************************************************************/
bool InitGameState(uint8_t Priority)
{
  ES_Event_t ThisEvent;

  MyPriority = Priority;
  // put us into the Initial PseudoState
  CurrentState = InitPState;
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
     PostGameState

 Parameters
     EF_Event_t ThisEvent , the event to post to the queue

 Returns
     boolean False if the Enqueue operation failed, True otherwise

 Description
     Posts an event to this state machine's queue
 Notes

 Author
   K Cao, 10/28/20
****************************************************************************/
bool PostGameState(ES_Event_t ThisEvent)
{
  return ES_PostToService(MyPriority, ThisEvent);
}

/****************************************************************************
 Function
    RunGameState

 Parameters
   ES_Event_t : the event to process

 Returns
   ES_Event_t, ES_NO_EVENT if no error ES_ERROR otherwise

 Description
   add your description here
 Notes
   uses nested switch/case to implement the machine.
 Author
   K Cao, 10/28/20
****************************************************************************/
ES_Event_t RunGameState(ES_Event_t ThisEvent)
{
  ES_Event_t ReturnEvent;
  ReturnEvent.EventType = ES_NO_EVENT; 

  switch (CurrentState)
  {
    case InitPState:       
    {
      if (ThisEvent.EventType == ES_INIT)    
      {
        for (uint8_t i = 0; i < 3; i++)
        {
          highScores[i] = 0;
        }
        ES_Event_t DisplayEvent;
        DisplayEvent.EventType = ES_DISPLAY_WELCOME;
        //PostDisplay(DisplayEvent);

        ES_Event_t DotstarEvent;
        DotstarEvent.EventType = ES_RANDOM;
        //PostDotstar(DotstarEvent);
        CurrentState = WelcomeScreen;
      }
    }
    break;

    case WelcomeScreen:        
    {
      switch (ThisEvent.EventType)
      {
        case ES_SENSOR_PRESSED:
        {   
          roundNumber = 1;
          ES_Event_t DisplayEvent;
          DisplayEvent.EventType = ES_DISPLAY_READY;
          DisplayEvent.EventParam = roundNumber;
          //PostDisplay(DisplayEvent);

          ES_Event_t DotstarEvent;
          DotstarEvent.EventType = ES_OFF;
          //PostDotstar(DotstarEvent);

          ES_Timer_Init(1, 2000);       // ReadyTimer
          CurrentState = GALeader;
        }
        break;

        default:
          ;
      } 
    }
    break;

    case GALeader:       
    {
      switch (ThisEvent.EventType)
      {
        case ES_GAME_START:
        {   
          ES_Event_t DisplayEvent;
          DisplayEvent.EventType = ES_DISPLAY_GO;
          //PostDisplay(DisplayEvent);

          ES_Timer_Init(2, 2000);       // GoTimer
          CurrentState = GAFollower;
        }
        break;

        default:
          ;
      } 
    }
    break;

    case GAFollower:        
    {
      switch (ThisEvent.EventType)
      {
        case ES_ROUND_COMPLETE:
        {   
          ES_Event_t DisplayEvent;
          DisplayEvent.EventType = ES_DISPLAY_ROUNDCOMPLETE;
          //PostDisplay(DisplayEvent);

          ES_Event_t DotstarEvent;
          DotstarEvent.EventType = ES_GREEN;
          //PostDotstar(DotstarEvent);
          CurrentState = GARoundComplete;
        }
        break;

        case ES_GAME_COMPLETE:
        {   
          uint16_t score = ThisEvent.EventParam;
          ES_Event_t DisplayEvent;
          ES_Event_t DotstarEvent;
          DisplayEvent.EventType = ES_DISPLAY_GAMECOMPLETE;
          //if (UpdateHighScore(score)){
          //  DisplayEvent.EventParam = score;
          //  DotstarEvent.EventType = ES_GREEN;
          //} else {
          //  DisplayEvent.EventParam = 0;
          //  DotstarEvent.EventType = ES_RED;
          //}
          //PostDisplay(DisplayEvent);
          //PostDotstar(DotstarEvent);
          ES_Timer_Init(3, 30000);      // GameOverTimer
          CurrentState = GameComplete;
        }
        break;

        default:
          ;
      } 
    }
    break;

    case GARoundComplete:      
    {
      switch (ThisEvent.EventType)
      {
        case ES_SENSOR_PRESSED:
        {   
          roundNumber++;
          ES_Event_t DisplayEvent;
          DisplayEvent.EventType = ES_DISPLAY_READY;
          DisplayEvent.EventParam = roundNumber;
          //PostDisplay(DisplayEvent);

          ES_Event_t DotstarEvent;
          DotstarEvent.EventType = ES_OFF;
          //PostDotstar(DotstarEvent);

          ES_Timer_Init(1, 2000);       // ReadyTimer
          CurrentState = GALeader;
        }
        break;

        default:
          ;
      } 
    }
    break;

    case GameComplete:        
    {
      switch (ThisEvent.EventType)
      {
        case ES_SENSOR_PRESSED:
        {   
          ES_Event_t DisplayEvent;
          DisplayEvent.EventType = ES_DISPLAY_WELCOME;
          //PostDisplay(DisplayEvent);

          ES_Event_t DotstarEvent;
          DotstarEvent.EventType = ES_RANDOM;
          //PostDotstar(DotstarEvent);
          CurrentState = WelcomeScreen;
        }
        break;

        case ES_TIMEOUT:
        {   
          if (ThisEvent.EventParam == GAMEOVER_TIMER) {
            ES_Event_t DisplayEvent;
            DisplayEvent.EventType = ES_DISPLAY_WELCOME;
            //PostDisplay(DisplayEvent);

            ES_Event_t DotstarEvent;
            DotstarEvent.EventType = ES_RANDOM;
            //PostDotstar(DotstarEvent);
            CurrentState = WelcomeScreen;
          }
        }
        break;

        default:
          ;
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
     QueryTemplateSM

 Parameters
     None

 Returns
     GameState_t The current state of the Template state machine

 Description
     returns the current state of the Template state machine
 Notes

 Author
     J. Edward Carryer, 10/23/11, 19:21
****************************************************************************/
GameState_t QueryGameState(void)
{
  return CurrentState;
}

/***************************************************************************
 event checkers
 ***************************************************************************/
bool CheckTouchSensor(){
  bool eventStatus = false;
  if ((CurrentState == WelcomeScreen) || (CurrentState == GARoundComplete) 
      || (CurrentState == GameComplete)){
    uint8_t currentButtonState = digitalRead(SENSOR_INPUT_PIN);
    if((currentButtonState != lastButtonState) && (currentButtonState == LOW)){
      ES_Event_t ThisEvent;
      ThisEvent.EventType = ES_SENSOR_PRESSED;
      PostGameState(ThisEvent);
      eventStatus = true;
    }
  lastButtonState = currentButtonState;
  }
  return eventStatus;
}

/***************************************************************************
 private functions
 ***************************************************************************/

