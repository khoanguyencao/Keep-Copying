/****************************************************************************
 Module
   MasterReset.c

 Revision
   1.0.1

 Description
   This is a template file for implementing flat state machines under the
   Gen2 Events and Services Framework.

 Notes

 History
 When           Who     What/Why
 -------------- ---     --------
 10/30/20       kcao    Creation of file 
****************************************************************************/
/*----------------------------- Include Files -----------------------------*/
/* include header files for this state machine as well as any machines at the
   next lower level in the hierarchy that are sub-machines to this machine
*/
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "MasterReset.h"
#include "GameState.h"
#include "Seq.h"

/*----------------------------- Module Defines ----------------------------*/

/*---------------------------- Module Functions ---------------------------*/
/* prototypes for private functions for this machine.They should be functions
   relevant to the behavior of this state machine
*/

/*---------------------------- Module Variables ---------------------------*/
// everybody needs a state variable, you may need others as well.
// type of state variable should match htat of enum in header file
static MasterResetState_t CurrentState;

// with the introduction of Gen2, we need a module level Priority var as well
static uint8_t MyPriority;

/*------------------------------ Module Code ------------------------------*/
/****************************************************************************
 Function
     InitMasterReset

 Parameters
     uint8_t : the priorty of this service

 Returns
     bool, false if error in initialization, true otherwise

 Description
     Saves away the priority, sets up the initial transition and does any
     other required initialization for this state machine
 Notes

 Author
     K. Cao
****************************************************************************/
bool InitMasterReset(uint8_t Priority)
{
  ES_Event_t InitEvent;
  MyPriority = Priority;
  CurrentState = InitMR;
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
     PostMasterReset

 Parameters
     EF_Event_t ThisEvent , the event to post to the queue

 Returns
     boolean False if the Enqueue operation failed, True otherwise

 Description
     Posts an event to this state machine's queue
 Notes

 Author
     K. Cao
****************************************************************************/
bool PostMasterReset(ES_Event_t ThisEvent)
{
  return ES_PostToService(MyPriority, ThisEvent);
}

/****************************************************************************
 Function
    RunMasterReset

 Parameters
   ES_Event_t : the event to process

 Returns
   ES_Event_t, ES_NO_EVENT if no error ES_ERROR otherwise

 Description
   add your description here
 Notes
   uses nested switch/case to implement the machine.
 Author
   K. Cao
****************************************************************************/
ES_Event_t RunMasterReset(ES_Event_t ThisEvent)
{
  ES_Event_t ReturnEvent;
  ReturnEvent.EventType = ES_NO_EVENT;

  switch (CurrentState)
  {
    case InitMR:     
    {
      if (ThisEvent.EventType == ES_INIT)  
      {
        ES_Timer_InitTimer(IDLE_TIMER, 30000);
        CurrentState = Waiting;
      }
    }
    break;

    case Waiting:    
    {
      switch (ThisEvent.EventType)
      {
        case ES_INPUT_DETECTED:
        {
            printf("Master Reset Input detected\r\n");
          ES_Timer_InitTimer(IDLE_TIMER, 30000);
        }
        break;

        case ES_TIMEOUT:
        {   
          if (ThisEvent.EventParam == IDLE_TIMER)
          {
            ES_Event_t ResetEvent;
            ResetEvent.EventType = ES_MASTER_RESET;
            PostGameState(ResetEvent);
            PostSequence(ResetEvent);
            printf("Master Reset\r\n");
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
