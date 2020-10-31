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

bool Check4WriteDone(void);
        

#endif /* GameState_H */

