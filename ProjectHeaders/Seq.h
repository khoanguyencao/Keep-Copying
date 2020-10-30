/* 
 * File:   Seq.h
 * Author: chris
 *
 * Created on October 28, 2020, 7:09 AM
 */

#ifndef SEQ_H
#define	SEQ_H

#include <stdint.h>
#include <stdbool.h>

#include <xc.h>
#include <p32xxxx.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/attribs.h>
#include <sys/kmem.h>

#include "ES_Configure.h"
#include "ES_Framework.h"
#include "ES_DeferRecall.h"
#include "ES_ShortTimer.h"
#include "ES_Port.h"

//type def
typedef enum{
    PseudoInit=0,
    SequenceCreate,
    SequenceDisplay,
    SequenceInput
}SequenceState_t;

//functions
bool InitSequence(uint8_t Priority);
bool PostSequence(ES_Event_t ThisEvent);
ES_Event_t RunSequence(ES_Event_t ThisEvent);

//Event Checker
bool CheckXYVal (void);

//Complementary functions
bool Input_Check(uint32_t *adcResults);

#endif	/* SEQ_H */

