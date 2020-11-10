#ifndef GameState_H
#define GameState_H

// Event Definitions
#include "ES_Configure.h" /* gets us event definitions */
#include "ES_Types.h"     /* gets bool type for returns */

// States in FSM
typedef enum
{
  InitPState, WelcomeScreen, GALeader, GAFollower, GARoundComplete, 
  GameComplete, Demo
}GameState_t;

// Public Function Prototypes
bool InitGameState(uint8_t Priority);
bool PostGameState(ES_Event_t ThisEvent);
ES_Event_t RunGameState(ES_Event_t ThisEvent);

// Event Checkers
bool CheckTouchSensor();

// Query Functions
void queryHighScores(uint16_t* score1, uint16_t* score2, uint16_t* score3);

#endif /* GameState_H */

