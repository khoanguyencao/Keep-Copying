/****************************************************************************

  Header file for template Flat Sate Machine
  based on the Gen2 Events and Services Framework

 ****************************************************************************/

#ifndef Dotstar_H
#define Dotstar_H

// Event Definitions
#include "ES_Configure.h" /* gets us event definitions */
#include "ES_Types.h"     /* gets bool type for returns */

// typedefs for the states
// State definitions for use with the query function
typedef enum
{
  DotstarInitPState, DotstarRed, DotstarGreen, DotstarRandom, DotstarOff
}DotstarState_t;

// Public Function Prototypes

bool InitDotstar(uint8_t Priority);
bool PostDotstar(ES_Event_t ThisEvent);
ES_Event_t RunDotstar(ES_Event_t ThisEvent);
DotstarState_t QueryDotstar(void);
void dotStar_Write(uint8_t Bright1, uint8_t Red1, uint8_t Blue1, uint8_t Green1, 
            uint8_t Bright2, uint8_t Red2, uint8_t Blue2, uint8_t Green2);
        

#endif /* Dotstar_H */

