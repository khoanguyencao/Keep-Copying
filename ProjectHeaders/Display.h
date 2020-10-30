/****************************************************************************

  Header file for template Flat Sate Machine
  based on the Gen2 Events and Services Framework

 ****************************************************************************/

#ifndef Display_H
#define Display_H

// Event Definitions
#include "ES_Configure.h" /* gets us event definitions */
#include "ES_Types.h"     /* gets bool type for returns */

// typedefs for the states
// State definitions for use with the query function
typedef enum
{
  DisplayInitPState, DisplayAvailable, DisplayBusy
}DisplayState_t;

// Public Function Prototypes

bool InitDisplay(uint8_t Priority);
bool PostDisplay(ES_Event_t ThisEvent);
ES_Event_t RunDisplay(ES_Event_t ThisEvent);
DisplayState_t QueryDisplay(void);
void welcomeScreen(void);
void readyScreen(uint16_t score, uint16_t round);
void instructionScreen(uint16_t score, uint16_t round, uint16_t instruction);
void goScreen(uint16_t score, uint16_t round);
void playScreen(uint16_t score, uint16_t time, uint16_t input);
void roundCompleteScreen(uint16_t score, uint16_t round);
void gameCompleteScreen(void);
static void bitUnpack(uint16_t EventParam, uint16_t* score, uint8_t* time, uint8_t* input);
bool Check4WriteDone(void);
        

#endif /* GameState_H */

