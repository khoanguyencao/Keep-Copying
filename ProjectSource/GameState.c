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
 11/03/20       kcao    Implementation of Demo
 10/31/20       kcao    Integration with Dotstar Service
 10/30/20       kcao    Integration with Display Service
 10/29/20       kcao    Integration with Sequence State Machine 
 10/28/20       kcao    File creation 
****************************************************************************/
/*----------------------------- Include Files -----------------------------*/
/* include header files for this state machine as well as any machines at the
   next lower level in the hierarchy that are sub-machines to this machine
*/
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "GameState.h"
#include "hal.h"
#include "Seq.h"
#include "Display.h"
#include "Dotstar.h"
#include "MasterReset.h"

/*----------------------------- Module Defines ----------------------------*/

#define SENSOR_INPUT_PIN 10 // corresponds to real pin 11 for touch sensor

/*---------------------------- Module Functions ---------------------------*/
/* prototypes for private functions for this machine.They should be functions
   relevant to the behavior of this state machine
*/
static bool UpdateHighScores(const uint16_t score);
static int compareScores(const void *a, const void *b);
static void masterReset();

/*---------------------------- Module Variables ---------------------------*/
// everybody needs a state variable, you may need others as well.
// type of state variable should match htat of enum in header file
static GameState_t CurrentState;
static uint16_t highScores[4];
static uint16_t roundNumber;
static uint8_t lastTouchSensorState;

// with the introduction of Gen2, we need a module level Priority var as well
static uint8_t MyPriority;

/*------------------------------ Module Code ------------------------------*/
/****************************************************************************
 Function
     InitGameState

 Parameters
     uint8_t : the priority of this service

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
  ES_Event_t InitEvent;
  MyPriority = Priority;
  CurrentState = InitPState;
  InitEvent.EventType = ES_INIT;

  if (ES_PostToService(MyPriority, InitEvent) == true){
    return true;
  } else {
    return false;
  }
}

/****************************************************************************
 Function
     PostGameState

 Parameters
     EF_Event_t ThisEvent, the event to post to the queue

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
   State machine that manages what the current game state is and communicates
   directly with the display and dotstar. The FSM also manages the scores.
  
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
        // Init high scores
        for (uint8_t i = 0; i < 4; i++)
        {
          highScores[i] = 0;
        }
        
        // Update display to Welcome Screen
        ES_Event_t DisplayEvent;
        DisplayEvent.EventType = ES_DISPLAY_WELCOME;
        PostDisplay(DisplayEvent);
        
        // Update dotstar to be on random colors
        ES_Event_t DotstarEvent;
        DotstarEvent.EventType = ES_RANDOM;
        PostDotstar(DotstarEvent);

        // Init touch sensor state and demo timer  
        lastTouchSensorState = digitalRead(SENSOR_INPUT_PIN);
        ES_Timer_InitTimer(DEMO_TIMER, 15000);
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
          // Update display with ready screen and round number 
          roundNumber = 1;
          ES_Event_t DisplayEvent;
          DisplayEvent.EventType = ES_DISPLAY_READY;
          DisplayEvent.EventParam = roundNumber;
          PostDisplay(DisplayEvent);

          // Update dotstar to be off         
          ES_Event_t DotstarEvent;
          DotstarEvent.EventType = ES_OFF;
          PostDotstar(DotstarEvent);
          
          // Update sequence state machine for first round
          ES_Event_t SequenceEvent;
          SequenceEvent.EventType = ES_FIRST_ROUND;
          PostSequence(SequenceEvent);

          // Init ready timer
          ES_Timer_InitTimer(READY_TIMER, 1000);
          CurrentState = GALeader;
        }
        break;

        case ES_TIMEOUT:
        {
          if (ThisEvent.EventParam == DEMO_TIMER)
          {
            // Update display with Demo Screen
            ES_Event_t DisplayEvent;
            DisplayEvent.EventType = ES_DISPLAY_DEMO;
            PostDisplay(DisplayEvent);

            // Update sequence state machine for first round
            ES_Event_t SequenceEvent;
            SequenceEvent.EventType = ES_FIRST_ROUND;
            PostSequence(SequenceEvent);

            // Init demo screen timer
            ES_Timer_InitTimer(DEMO_SCREEN_TIMER, 1000);
            CurrentState = Demo;
          }
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
        case ES_TIMEOUT:
        {   
          if (ThisEvent.EventParam == LAST_DIRECTION_TIMER)
          {
            // Update display with Go Screen
            ES_Event_t DisplayEvent;
            DisplayEvent.EventType = ES_DISPLAY_GO;
            PostDisplay(DisplayEvent);

            // Init Go Timer
            ES_Timer_InitTimer(GO_TIMER, 1000);
            CurrentState = GAFollower;
          }
        }
        break;

        case ES_MASTER_RESET:
        {
            masterReset();
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
          // Update display to Round Complete Screen
          ES_Event_t DisplayEvent;
          DisplayEvent.EventType = ES_DISPLAY_ROUNDCOMPLETE;
          PostDisplay(DisplayEvent);

          // Update dotstar to flash green
          ES_Event_t DotstarEvent;
          DotstarEvent.EventType = ES_GREEN;
          PostDotstar(DotstarEvent);

          CurrentState = GARoundComplete;
        }
        break;

        case ES_GAME_COMPLETE:
        {   
          // Update display to Game Complete Screen
          ES_Event_t DisplayEvent;
          DisplayEvent.EventType = ES_DISPLAY_GAMECOMPLETE;
          PostDisplay(DisplayEvent);
          
          // Update dotstar to flash green/red based on whether high score achieved
          uint16_t score = ThisEvent.EventParam;
          ES_Event_t DotstarEvent;
          if (UpdateHighScores(score)){
            DotstarEvent.EventType = ES_GREEN;
          } else {
            DotstarEvent.EventType = ES_RED;
          }
          PostDotstar(DotstarEvent);

          // Init Game Over Timer
          ES_Timer_InitTimer(GAMEOVER_TIMER, 30000);
          CurrentState = GameComplete;
        }
        break;

        case ES_MASTER_RESET:
        {
            masterReset();
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
          // Update display to Ready Screen with round number 
          roundNumber++;
          ES_Event_t DisplayEvent;
          DisplayEvent.EventType = ES_DISPLAY_READY;
          DisplayEvent.EventParam = roundNumber;
          PostDisplay(DisplayEvent);
          
          // Update dotstar to turn off
          ES_Event_t DotstarEvent;
          DotstarEvent.EventType = ES_OFF;
          PostDotstar(DotstarEvent);

          // Init Ready Timer
          ES_Timer_InitTimer(READY_TIMER, 1000);
          CurrentState = GALeader;
        }
        break;

        case ES_MASTER_RESET:
        {
            masterReset();
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
          // Update display to Welcome Screen  
          ES_Event_t DisplayEvent;
          DisplayEvent.EventType = ES_DISPLAY_WELCOME;
          PostDisplay(DisplayEvent);

          // Update dotstar with random colors
          ES_Event_t DotstarEvent;
          DotstarEvent.EventType = ES_RANDOM;
          PostDotstar(DotstarEvent);
          
          // Init Demo Timer 
          ES_Timer_InitTimer(DEMO_TIMER, 15000);
          CurrentState = WelcomeScreen;
        }
        break;

        case ES_TIMEOUT:
        {   
          if (ThisEvent.EventParam == GAMEOVER_TIMER){
          // Update display to Welcome Screen  
          ES_Event_t DisplayEvent;
          DisplayEvent.EventType = ES_DISPLAY_WELCOME;
          PostDisplay(DisplayEvent);

          // Update dotstar with random colors
          ES_Event_t DotstarEvent;
          DotstarEvent.EventType = ES_RANDOM;
          PostDotstar(DotstarEvent);
          
          // Init Demo Timer 
          ES_Timer_InitTimer(DEMO_TIMER, 15000);
          CurrentState = WelcomeScreen;
          }
        }
        break;

        case ES_MASTER_RESET:
        {
            masterReset();
        }
        break;
        
        default:
          ;
      } 
    }
    break;

    case Demo:       
    {
      switch (ThisEvent.EventType)
      {
        case ES_TIMEOUT:
        {   
          if (ThisEvent.EventParam == LAST_DIRECTION_TIMER){
            // Complete a master reset of both the game state and sequence FSMs
            masterReset();
            ES_Event_t SequenceEvent;
            SequenceEvent.EventType = ES_MASTER_RESET;
            PostSequence(SequenceEvent);
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
   queryHighScores

 Parameters
   Three uint16_t passed by reference

 Returns
   Nothing

 Description
   Query function for the display to update scores. Three unsigned 
   16-bit integers must be passed by reference.

 Author
   K Cao, 10/28/20
****************************************************************************/
void queryHighScores(uint16_t* score1, uint16_t* score2, uint16_t* score3){
  *score1 = highScores[0];
  *score2 = highScores[1];
  *score3 = highScores[2];
}

/***************************************************************************
 event checkers
 ***************************************************************************/

/****************************************************************************
 Function
   CheckTouchSensor

 Parameters
   Nothing

 Returns
   bool, true if touch sensor changes from pressed to unpressed

 Description
   Event checker to check if touch sensor pressed.

 Notes
   Only checks in specific states - WelcomeScreen, GARoundComplete, 
   GameComplete

 Author
   K Cao, 10/28/20
****************************************************************************/
bool CheckTouchSensor(){
  bool eventStatus = false;
  if ((CurrentState == WelcomeScreen) || (CurrentState == GARoundComplete) || 
      (CurrentState == GameComplete)) 
  {
    uint8_t currentTouchSensorState = digitalRead(SENSOR_INPUT_PIN);
    if ((currentTouchSensorState != lastTouchSensorState) && 
        (currentTouchSensorState == LOW)){
      // Update game state of touch sensor press
      ES_Event_t TouchSensorEvent;
      TouchSensorEvent.EventType = ES_SENSOR_PRESSED;
      PostGameState(TouchSensorEvent);
      
      // Update master reset state machine of a detected input
      ES_Event_t InputEvent;
      InputEvent.EventType = ES_INPUT_DETECTED;
      PostMasterReset(InputEvent);

      eventStatus = true;
    }
  lastTouchSensorState = currentTouchSensorState;
  }
  return eventStatus;
}

/****************************************************************************
 Function
   UpdateHighScores

 Parameters
   uint16_t score, achieved by the player after game is complete

 Returns
   bool, true if latest score in top 3, false if not 

 Description
   Helper function that maintains and updates the high scores.

 Notes
   Newest score written to fourth array component before being sorted with 
   QuickSort.

 Author
   K Cao, 10/28/20
****************************************************************************/
static bool UpdateHighScores(const uint16_t score){
  // Sort high scores with QuickSort
  highScores[3] = score;
  qsort(highScores, 4, 2, compareScores);
  // Check if in top 3 scores
  bool highScoreFlag = false;
  for (uint8_t i = 0; i < 3; i++){
    if (highScores[i] == score){
      highScoreFlag = true;
      break;
    }
  }
  return highScoreFlag;
}

/****************************************************************************
 Function
   compareScores

 Parameters
   Two void pointers

 Returns
   Integer value - positive if b is greater than a, negative if a is greater
   than b, and zero if a is equal to b.

 Description
   Comparison function for two unsigned 16-bit integers that returns an 
   integer value based on strcmp standards.

 Notes
   Required for C's implementation of qsort.

 Author
   K Cao, 10/28/20
****************************************************************************/
static int compareScores(const void *a, const void *b){
  return *(const uint16_t *)b - *(const uint16_t *)a;
}

/****************************************************************************
 Function
   masterReset

 Parameters
   Nothing

 Returns
   Nothing

 Description
   Completes a master reset of the display, dotstar and demo timers.

 Notes

 Author
   K Cao, 10/28/20
****************************************************************************/
static void masterReset(){
  // Update display to Welcome Screen
  ES_Event_t DisplayEvent;
  DisplayEvent.EventType = ES_DISPLAY_WELCOME;
  PostDisplay(DisplayEvent);

  // Update dotstar to random colors
  ES_Event_t DotstarEvent;
  DotstarEvent.EventType = ES_RANDOM;
  PostDotstar(DotstarEvent);

  // Init Demo Timer
  ES_Timer_InitTimer(DEMO_TIMER, 15000);
  CurrentState = WelcomeScreen;
}