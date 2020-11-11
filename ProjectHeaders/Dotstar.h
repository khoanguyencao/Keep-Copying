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
static void dotStar_Write(const uint8_t Bright1, const uint8_t Red1, const uint8_t Blue1, 
        const uint8_t Green1, const uint8_t Bright2, const uint8_t Red2, const uint8_t Blue2, 
        const uint8_t Green2);
        

#endif /* Dotstar_H */

