#ifndef MasterReset_H
#define MasterReset_H

// Event Definitions
#include "ES_Configure.h" /* gets us event definitions */
#include "ES_Types.h"     /* gets bool type for returns */

// typedefs for the states
// State definitions for use with the query function
typedef enum
{
  InitMR, Waiting
}MasterResetState_t;

// Public Function Prototypes

bool InitMasterReset(uint8_t Priority);
bool PostMasterReset(ES_Event_t ThisEvent);
ES_Event_t RunMasterReset(ES_Event_t ThisEvent);

#endif /* MasterReset_H */

