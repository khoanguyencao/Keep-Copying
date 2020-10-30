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
#include "hal.h"
#include "Seq.h"
#include "Display.h"

/*----------------------------- Module Defines ----------------------------*/

#define SENSOR_INPUT_PIN 10 // corresponds to real pin 11 for touch sensor

/*---------------------------- Module Functions ---------------------------*/
/* prototypes for private functions for this machine.They should be functions
   relevant to the behavior of this state machine
*/

static bool UpdateHighScores(uint16_t score);
static int compareScores(const void *a, const void *b);

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
  ES_Event_t InitEvent;
  MyPriority = Priority;
  CurrentState = InitPState;
  InitEvent.EventType = ES_INIT;
  // Set touch sensor (RB4) as a digital input
  TRISBbits.TRISB4 = 1;

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
        lastTouchSensorState = digitalRead(SENSOR_INPUT_PIN);
        for (uint8_t i = 0; i < 4; i++){
          highScores[i] = 0;
        }
        ES_Event_t DisplayEvent;
        DisplayEvent.EventType = ES_DISPLAY_WELCOME;
        PostDisplay(DisplayEvent);
        printf("Welcome Screen\r\n");

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
          PostDisplay(DisplayEvent);
          printf("Ready Screen\r\n");

          ES_Event_t DotstarEvent;
          DotstarEvent.EventType = ES_OFF;
          //PostDotstar(DotstarEvent);

          ES_Timer_InitTimer(READY_TIMER, 2000);       
          CurrentState = GALeader;
         
          ES_Event_t SequenceRandomizer;
          SequenceRandomizer.EventType = ES_FIRST_ROUND;
          SequenceRandomizer.EventParam = ES_Timer_GetTime();
          PostSequence(SequenceRandomizer);
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
          if (ThisEvent.EventParam == LAST_DIRECTION_TIMER){
            ES_Event_t DisplayEvent;
            DisplayEvent.EventType = ES_DISPLAY_GO;
            PostDisplay(DisplayEvent);
            printf("Go Screen\r\n");

            ES_Timer_InitTimer(GO_TIMER, 2000);
            CurrentState = GAFollower;
          }
          
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
          PostDisplay(DisplayEvent);
          printf("Round Complete Screen\r\n");

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
          if (UpdateHighScores(score)){
            DotstarEvent.EventType = ES_GREEN;
          } else {
            DotstarEvent.EventType = ES_RED;
          }
          PostDisplay(DisplayEvent);
          //PostDotstar(DotstarEvent);
          ES_Timer_InitTimer(GAMEOVER_TIMER, 30000);
          CurrentState = GameComplete;
          printf("Game Complete Screen\r\n");
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
          PostDisplay(DisplayEvent);
          printf("Ready Screen\r\n");

          ES_Event_t DotstarEvent;
          DotstarEvent.EventType = ES_OFF;
          //PostDotstar(DotstarEvent);

          ES_Timer_InitTimer(READY_TIMER, 2000);
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
          PostDisplay(DisplayEvent);
          printf("Welcome Screen\r\n");

          ES_Event_t DotstarEvent;
          DotstarEvent.EventType = ES_RANDOM;
          //PostDotstar(DotstarEvent);
          CurrentState = WelcomeScreen;
        }
        break;

        case ES_TIMEOUT:
        {   
          if (ThisEvent.EventParam == GAMEOVER_TIMER){
            ES_Event_t DisplayEvent;
            DisplayEvent.EventType = ES_DISPLAY_WELCOME;
            PostDisplay(DisplayEvent);
            printf("Welcome Screen\r\n");

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

// Need to pass by reference (queryHighScores(&score1, &score2, &score3))
void queryHighScores(uint16_t* score1, uint16_t* score2, uint16_t* score3){
  *score1 = highScores[0];
  *score2 = highScores[1];
  *score3 = highScores[2];
}

/***************************************************************************
 event checkers
 ***************************************************************************/
bool CheckTouchSensor(){
  bool eventStatus = false;
  if ((CurrentState == WelcomeScreen) || 
      (CurrentState == GARoundComplete) || 
      (CurrentState == GameComplete)){
    uint8_t currentTouchSensorState = digitalRead(SENSOR_INPUT_PIN);
    if ((currentTouchSensorState != lastTouchSensorState) && (currentTouchSensorState == LOW)){
      ES_Event_t ThisEvent;
      ThisEvent.EventType = ES_SENSOR_PRESSED;
      PostGameState(ThisEvent);
      eventStatus = true;
      printf("Touch Sensor Pressed\r\n");
    }
  lastTouchSensorState = currentTouchSensorState;
  }
  return eventStatus;
}

/***************************************************************************
 private functions
 ***************************************************************************/
// Update Function for High Scores
// Note maintained as uint16_t here to ease display service query
static bool UpdateHighScores(uint16_t score){
  // Sort high scores with QuickSort
  highScores[3] = score;
  qsort(highScores, 4, sizeof(uint16_t), compareScores);
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

// Comparison Function for Scores
static int compareScores(const void *a, const void *b){
  return *(const uint16_t *)a - *(const uint16_t *)b;
}