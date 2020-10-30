// This module
#include "Morse_Elements.h"
#include "Morse_Decoder.h"
#include "S1_OLED_Write.h"
#include "../u8g2Headers/portmap.h"
// Hardware
#include <xc.h>
#include <proc/p32mx170f256b.h>
#include <sys/attribs.h> // for ISR macors
#include <stdlib.h>
#include <string.h>
#include <proc/p32mx170f256b.h>
#include <sys/attribs.h> // for ISR macors

// Event & Services Framework
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "ES_DeferRecall.h"
#include "ES_ShortTimer.h"
#include "ES_Port.h"
#include "ES_Timers.h"
#include "EventCheckers.h"

/*----------------------------- Module Defines ----------------------------*/


/*---------------------------- Module Variables ---------------------------*/
// with the introduction of Gen2, we need a module level Priority variable
static uint8_t MyPriority;
static char morseStr[8]=""; //need to define otherwise counter doesnt work
static char *pmStr = morseStr; //pointer to char array
//Definitions for morse code elements
static char legalChars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890?.,:'-/()\"= !$&+;@_";
static char morseCode[][8] ={ ".-","-...","-.-.","-..",".","..-.","--.",
                      "....","..",".---","-.-",".-..","--","-.","---",
                      ".--.","--.-",".-.","...","-","..-","...-",
                      ".--","-..-","-.--","--..",".----","..---",
                      "...--","....-",".....","-....","--...","---..",
                      "----.","-----","..--..",".-.-.-","--..--",
                      "---...",".----.","-....-","-..-.","-.--.-",
                      "-.--.-",".-..-.","-...-","-.-.--","...-..-",
                      ".-...",".-.-.","-.-.-.",".--.-.","..--.-"
                     };
//counter variable for sizing string
  static uint32_t sl = 0;
/*------------------------------ Module Code ------------------------------*/
/****************************************************************************
 Function
     InitMorseDecoder
 Parameters
     uint8_t : the priorty of this service
 Returns
     bool, false if error in initialization, true otherwise
 Description
 Set event to Clear morse string variable
****************************************************************************/
bool InitMorse_Decoder(uint8_t Priority)
{
  ES_Event_t ThisEvent;

  MyPriority = Priority;    

        // post the initial transition event
        ThisEvent.EventType = ES_INIT;
  
          if (ES_PostToService(MyPriority, ThisEvent) == true)
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
     PostMorse_Decoder
 Parameters
     EF_Event ThisEvent ,the event to post to the queue
 Returns
     bool false if the Enqueue operation failed, true otherwise
 Description
     Posts an event to this state machine's queue
****************************************************************************/
bool PostMorse_Decoder(ES_Event_t ThisEvent)
{
  return ES_PostToService(MyPriority, ThisEvent);
}

/****************************************************************************
 Function
    RunMorse_Decoder
 Parameters
   ES_Event : the event to process
 Returns
   ES_Event, ES_NO_EVENT if no error ES_ERROR otherwise
 Description
 * Initializes decoder char string array to reset its value, add dot or dashes
 * upon receipt of a valid space it decodes the values in the char array and
 * posts to the oled. Bad spaces or calibration erases the decoder array value
****************************************************************************/
ES_Event_t RunMorse_Decoder(ES_Event_t ThisEvent)
{
  ES_Event_t ReturnEvent;
  ReturnEvent.EventType = ES_NO_EVENT; // assume no errors
  
 
/*-----------------------------------------------------------------------------
 * Current State switch case statement, Compares PS_INIT, and SEND_CHAR
 * --------------------------------------------------------------------------*/  
  switch (ThisEvent.EventType)
  {
    case ES_INIT:
    {
        //Clear morseStr
        *(pmStr)='\0';
        *(pmStr+1)='\0';
        *(pmStr+2)='\0';
        *(pmStr+3)='\0';
        *(pmStr+4)='\0';
        *(pmStr+5)='\0';
        *(pmStr+6)='\0';
        *(pmStr+7)='\0';
    }
    break;
    
    case ES_DOT://add dot
    {
        //measure array length and ensures no more than 8 elements are written
        if (sl < 8)
        {
            //Add dot to string
            morseStr[sl]='.';
            //printf("add dot %s \r\n",morseStr);
            //printf("counter %d \r\n",sl);
            //increase counter that measures array length
            sl++;
        }
        else
        {
            ReturnEvent.EventType = ES_ERROR;
        }
    }
    break;
    
    case ES_DASH://add dash
    {
        //measure array length and ensures no more than 8 elements are written
        if (sl < 8)
        {
            //Add dash to string
            morseStr[sl]='-';
            //printf("add dash %s \r\n",morseStr);
            //printf("counter %d \r\n",sl);
            //increase counter that measures array length
            sl++;
        }
        else
        {
            ReturnEvent.EventType = ES_ERROR;
        }
    }
    break;
    
    case ES_EOC_DETECTED://end of character detected
    {
        ThisEvent.EventType = ES_WRITE;
        //Decode Morse STring
        ThisEvent.EventParam = DecodeMorseString();

        //Clear morseString and counter
        *(pmStr)='\0';
        *(pmStr+1)='\0';
        *(pmStr+2)='\0';
        *(pmStr+3)='\0';
        *(pmStr+4)='\0';
        *(pmStr+5)='\0';
        *(pmStr+6)='\0';
        *(pmStr+7)='\0';
        //printf("ms %s \r\n",morseStr);
        sl = 0; //reset counter for morse length
        
        //Print character to OLED by posting
        PostS1_OLED_Write(ThisEvent);
    }
    break;
    
    case ES_EOW_DETECTED://end of word detected
    {
        ThisEvent.EventType = ES_WRITE;
        //Decode Morse STring
        ThisEvent.EventParam=DecodeMorseString();

        //Clear morseString and counter
        *(pmStr)='\0';
        *(pmStr+1)='\0';
        *(pmStr+2)='\0';
        *(pmStr+3)='\0';
        *(pmStr+4)='\0';
        *(pmStr+5)='\0';
        *(pmStr+6)='\0';
        *(pmStr+7)='\0';
        sl = 0;
        //Print character to OLED by posting
        PostS1_OLED_Write(ThisEvent);
        //Print space using event deferral of S1_OLED_Write
        ThisEvent.EventParam=' ';
        PostS1_OLED_Write(ThisEvent);
    }
    break;
    
    case ES_BAD_SPACE:
    {
        //Clear morseString
        *(pmStr)='\0';
        *(pmStr+1)='\0';
        *(pmStr+2)='\0';
        *(pmStr+3)='\0';
        *(pmStr+4)='\0';
        *(pmStr+5)='\0';
        *(pmStr+6)='\0';
        *(pmStr+7)='\0';
    }
    break;
    
    case ES_BAD_PULSE:
    {
        //Clear morseString
        *(pmStr)='\0';
        *(pmStr+1)='\0';
        *(pmStr+2)='\0';
        *(pmStr+3)='\0';
        *(pmStr+4)='\0';
        *(pmStr+5)='\0';
        *(pmStr+6)='\0';
        *(pmStr+7)='\0';
    }
    break;
    
    //Calibration
    case ES_PRESS:
    {
        //Clear morseString
        *(pmStr)='\0';
        *(pmStr+1)='\0';
        *(pmStr+2)='\0';
        *(pmStr+3)='\0';
        *(pmStr+4)='\0';
        *(pmStr+5)='\0';
        *(pmStr+6)='\0';
        *(pmStr+7)='\0';
    }
    break;
    
    default:
    {}
     break;
  }

  return ReturnEvent;
}

/*----------------------------------------------------------------------------
 * Decoder function
 * Takes no parameters, returns character
 * compares char array to morse definitions
 * returns morse decoded character
 ---------------------------------------------------------------------------*/
char DecodeMorseString(void)
{
    //Static Counter variable
    static uint8_t i;
    //compare char array across all 56 morse possibilities
    for (i=0;i<56;)
    {
        //printf("ms %s \r\n",morseStr);
        //printf("mc %s \r\n",morseCode[i]);
        if (strcmp(morseStr, morseCode[i]) == 0)
        {
            printf("char %c \r\n",legalChars[i]);//debug tool
            return legalChars[i];
        }
        i++;
    }
    return '~';//return error char if unable to decode
}
