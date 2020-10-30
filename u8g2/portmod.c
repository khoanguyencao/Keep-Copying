#include <xc.h>
#include "../u8g2Headers/portmap.h"

//Initialization function to set all ports to digital
void digiPin(void)
{
    ANSELA=0;
    ANSELB=0;
}

/*****************************************************************************
All functions can accept either int or pin_t. pin_t is a enum typedef
which maps a RXX port to an integer value
*************************************************************************/

/*****************************************************************************
Define prototype function to assign data direction (I/O)
Returns Void, accepts pin# as integer or RXX
Accepts INPUT / OUTPUT or integer 1,0 for Input/Output respectively
*****************************************************************************/
bool pinMode(pin_t pin, IO_t IO)
{
    //Identify which port to modify by using switch case statements
    switch(pin)
    {
        case 1:
            //Assign data direction to port
            //if IO not equal to 1 or 0 return false
            if (IO==1 || IO==0)
            {
                TRISAbits.TRISA0 = IO;
                return true;
            }
            else
            {
                return false;
            }
            break;
        case 2:
            //Assign data direction to port
            //if IO not equal to 1 or 0 return false
            if (IO==1 || IO==0)
            {
                TRISAbits.TRISA1 = IO;
                return true;
            }
            else
            {
                return false;
            }
            break;
        case 3:
            //Assign data direction to port
            //if IO not equal to 1 or 0 return false
            if (IO==1 || IO==0)
            {
                TRISAbits.TRISA2 = IO;
                return true;
            }
            else
            {
                return false;
            }
            break;  
        case 4:
            //Assign data direction to port
            //if IO not equal to 1 or 0 return false
            if (IO==1 || IO==0)
            {
                TRISAbits.TRISA3 = IO;
                return true;
            }
            else
            {
                return false;
            }
            break;
        case 5:
            //Assign data direction to port
            //if IO not equal to 1 or 0 return false
            if (IO==1 || IO==0)
            {
                TRISAbits.TRISA4 = IO;
                return true;
            }
            else
            {
                return false;
            }
            break;
        case 6:
            //Assign data direction to port
            //if IO not equal to 1 or 0 return false
            if (IO==1 || IO==0)
            {
                TRISBbits.TRISB0 = IO;
                return true;
            }
            else
            {
                return false;
            }
            break;
        case 7:
            //Assign data direction to port
            //if IO not equal to 1 or 0 return false
            if (IO==1 || IO==0)
            {
                TRISBbits.TRISB1 = IO;
                return true;
            }
            else
            {
                return false;
            }
            break;
        case 8:
            //Assign data direction to port
            //if IO not equal to 1 or 0 return false
            if (IO==1 || IO==0)
            {
                TRISBbits.TRISB2 = IO;
                return true;
            }
            else
            {
                return false;
            }
            break;
        case 9:
            //Assign data direction to port
            //if IO not equal to 1 or 0 return false
            if (IO==1 || IO==0)
            {
                TRISBbits.TRISB3 = IO;
                return true;
            }
            else
            {
                return false;
            }
            break;
        case 10:
            //Assign data direction to port
            //if IO not equal to 1 or 0 return false
            if (IO==1 || IO==0)
            {
                TRISBbits.TRISB4 = IO;
                return true;
            }
            else
            {
                return false;
            }
            break;
        case 11:
            //Assign data direction to port
            //if IO not equal to 1 or 0 return false
            if (IO==1 || IO==0)
            {
                TRISBbits.TRISB5 = IO;
                return true;
            }
            else
            {
                return false;
            }
            break;
        case 12:
            //Assign data direction to port
            //if IO not equal to 1 or 0 return false
            if (IO==1 || IO==0)
            {
                TRISBbits.TRISB6 = IO;
                return true;
            }
            else
            {
                return false;
            }
            break;
        case 13:
            //Assign data direction to port
            //if IO not equal to 1 or 0 return false
            if (IO==1 || IO==0)
            {
                TRISBbits.TRISB7 = IO;
                return true;
            }
            else
            {
                return false;
            }
            break;
        case 14:
            //Assign data direction to port
            //if IO not equal to 1 or 0 return false
            if (IO==1 || IO==0)
            {
                TRISBbits.TRISB8 = IO;
                return true;
            }
            else
            {
                return false;
            }
            break;
        case 15:
            //Assign data direction to port
            //if IO not equal to 1 or 0 return false
            if (IO==1 || IO==0)
            {
                TRISBbits.TRISB9 = IO;
                return true;
            }
            else
            {
                return false;
            }
            break;
        case 16:
            //Assign data direction to port
            //if IO not equal to 1 or 0 return false
            if (IO==1 || IO==0)
            {
                TRISBbits.TRISB10 = IO;
                return true;
            }
            else
            {
                return false;
            }
            break;
        case 17:
            //Assign data direction to port
            //if IO not equal to 1 or 0 return false
            if (IO==1 || IO==0)
            {
                TRISBbits.TRISB11 = IO;
                return true;
            }
            else
            {
                return false;
            }
            break;
        case 18:
            //Assign data direction to port
            //if IO not equal to 1 or 0 return false
            if (IO==1 || IO==0)
            {
                TRISBbits.TRISB12 = IO;
                return true;
            }
            else
            {
                return false;
            }
            break;
        case 19:
            //Assign data direction to port
            //if IO not equal to 1 or 0 return false
            if (IO==1 || IO==0)
            {
                TRISBbits.TRISB13 = IO;
                return true;
            }
            else
            {
                return false;
            }
            break;
        case 20:
            //Assign data direction to port
            //if IO not equal to 1 or 0 return false
            if (IO==1 || IO==0)
            {
                TRISBbits.TRISB14 = IO;
                return true;
            }
            else
            {
                return false;
            }
            break;
        case 21:
            //Assign data direction to port
            //if IO not equal to 1 or 0 return false
            if (IO==1 || IO==0)
            {
                TRISBbits.TRISB15 = IO;
                return true;
            }
            else
            {
                return false;
            }
            break;
        default:
            return false;
            break;
    }              
}

/*****************************************************************************
Define prototype function to write data
Returns Void, accepts pin# as RXX or integer value
Accepts HIGH, LOW or integer 1,0 for High/Low respectively
*****************************************************************************/
bool digitalWrite(pin_t pin, HL_t HL)
{
//Identify which port to modify by using switch case statements
    switch(pin)
    {
        case 1:
            //Write data to port
            //if HL not equal to 1 or 0, return false
            if (HL==1 || HL==0)
            {
                LATAbits.LATA0 = HL;
                return true;
            }
            else
            {
                return false;
            }
            break;
        case 2:
            //Write data to port
            //if HL not equal to 1 or 0, return false
            if (HL==1 || HL==0)
            {
                LATAbits.LATA1 = HL;
                return true;
            }
            else
            {
                return false;
            }
            break;
        case 3:
            //Write data to port
            //if HL not equal to 1 or 0, return false
            if (HL==1 || HL==0)
            {
                LATAbits.LATA2 = HL;
                return true;
            }
            else
            {
                return false;
            }
            break;  
        case 4:
            //Write data to port
            //if HL not equal to 1 or 0, return false
            if (HL==1 || HL==0)
            {
                LATAbits.LATA3 = HL;
                return true;
            }
            else
            {
                return false;
            }
            break;
        case 5:
            //Write data to port
            //if HL not equal to 1 or 0, return false
            if (HL==1 || HL==0)
            {
                LATAbits.LATA4 = HL;
                return true;
            }
            else
            {
                return false;
            }
            break;
        case 6:
            //Write data to port
            //if HL not equal to 1 or 0, return false
            if (HL==1 || HL==0)
            {
                LATBbits.LATB0 = HL;
                return true;
            }
            else
            {
                return false;
            }
            break;
        case 7:
            //Write data to port
            //if HL not equal to 1 or 0, return false
            if (HL==1 || HL==0)
            {
                LATBbits.LATB1 = HL;
                return true;
            }
            else
            {
                return false;
            }
            break;
        case 8:
            //Write data to port
            //if HL not equal to 1 or 0, return false
            if (HL==1 || HL==0)
            {
                LATBbits.LATB2 = HL;
                return true;
            }
            else
            {
                return false;
            }
            break;
        case 9:
            //Write data to port
            //if HL not equal to 1 or 0, return false
            if (HL==1 || HL==0)
            {
                LATBbits.LATB3 = HL;
                return true;
            }
            else
            {
                return false;
            }
            break;
        case 10:
            //Write data to port
            //if HL not equal to 1 or 0, return false
            if (HL==1 || HL==0)
            {
                LATBbits.LATB4 = HL;
                return true;
            }
            else
            {
                return false;
            }
            break;
        case 11:
            //Write data to port
            //if HL not equal to 1 or 0, return false
            if (HL==1 || HL==0)
            {
                LATBbits.LATB5 = HL;
                return true;
            }
            else
            {
                return false;
            }
            break;
        case 12:
            //Write data to port
            //if HL not equal to 1 or 0, return false
            if (HL==1 || HL==0)
            {
                LATBbits.LATB6 = HL;
                return true;
            }
            else
            {
                return false;
            }
            break;
        case 13:
            //Write data to port
            //if HL not equal to 1 or 0, return false
            if (HL==1 || HL==0)
            {
                LATBbits.LATB7 = HL;
                return true;
            }
            else
            {
                return false;
            }
            break;
        case 14:
            //Write data to port
            //if HL not equal to 1 or 0, return false
            if (HL==1 || HL==0)
            {
                LATBbits.LATB8 = HL;
                return true;
            }
            else
            {
                return false;
            }
            break;
        case 15:
            //Write data to port
            //if HL not equal to 1 or 0, return false
            if (HL==1 || HL==0)
            {
                LATBbits.LATB9 = HL;
                return true;
            }
            else
            {
                return false;
            }
            break;
        case 16:
            //Write data to port
            //if HL not equal to 1 or 0, return false
            if (HL==1 || HL==0)
            {
                LATBbits.LATB10 = HL;
                return true;
            }
            else
            {
                return false;
            }
            break;
        case 17:
            //Write data to port
            //if HL not equal to 1 or 0, return false
            if (HL==1 || HL==0)
            {
                LATBbits.LATB11 = HL;
                return true;
            }
            else
            {
                return false;
            }
            break;
        case 18:
            //Write data to port
            //if HL not equal to 1 or 0, return false
            if (HL==1 || HL==0)
            {
                LATBbits.LATB12 = HL;
                return true;
            }
            else
            {
                return false;
            }
            break;
        case 19:
            //Write data to port
            //if HL not equal to 1 or 0, return false
            if (HL==1 || HL==0)
            {
                LATBbits.LATB13 = HL;
                return true;
            }
            else
            {
                return false;
            }
            break;
        case 20:
            //Write data to port
            //if HL not equal to 1 or 0, return false
            if (HL==1 || HL==0)
            {
                LATBbits.LATB14 = HL;
                return true;
            }
            else
            {
                return false;
            }
            break;
        case 21:
            //Write data to port
            //if HL not equal to 1 or 0, return false
            if (HL==1 || HL==0)
            {
                LATBbits.LATB15 = HL;
                return true;
            }
            else
            {
                return false;
            }
            break;
        default:
            return false;
            break;
    }
}

/*******************************************************************************
Define prototype function to read data
Returns uint8_t, accepts pin# as RXX or integer value
 * ****************************************************************************/

uint8_t digitalRead(pin_t pin)
{
    //Initialize return variable
    uint8_t dR;
    //Identify which port to read by using switch case statements
    switch(pin)
    {
        case 1:
            //Read Port
            dR=PORTAbits.RA0;
            return dR;
            break;
        case 2:
            //Read Port
            dR=PORTAbits.RA1;
            return dR;
            break;
        case 3:
            //Read Port
            dR=PORTAbits.RA2;
            return dR;
            break; 
        case 4:
            //Read Port
            dR=PORTAbits.RA3;
            return dR;
            break;
        case 5:
            //Read Port
            dR=PORTAbits.RA4;
            //Return Variable
            return dR;
            break;
        case 6:
            //Read Port
            dR=PORTBbits.RB0;
            //Return Variable
            return dR;
            break;
        case 7:
            //Read Port
            dR=PORTBbits.RB1;
            //Return Variable
            return dR;
            break;
        case 8:
            //Read Port
            dR=PORTBbits.RB2;
            //Return Variable
            return dR;
            break;
        case 9:
            //Read Port
            dR=PORTBbits.RB3;
            //Return Variable
            return dR;
            break;
        case 10:
            //Read Port
            dR=PORTBbits.RB4;
            //Return Variable
            return dR;
            break;
        case 11:
            //Read Port
            dR=PORTBbits.RB5;
            //Return Variable
            return dR;
            break;
        case 12:
            //Read Port
            dR=PORTBbits.RB6;
            //Return Variable
            return dR;
            break;
        case 13:
            //Read Port
            dR=PORTBbits.RB7;
            //Return Variable
            return dR;
            break;
        case 14:
            //Read Port
            dR=PORTBbits.RB8;
            //Return Variable
            return dR;
            break;
        case 15:
            //Read Port
            dR=PORTBbits.RB9;
            //Return Variable
            return dR;
            break;
        case 16:
            //Read Port
            dR=PORTBbits.RB10;
            //Return Variable
            return dR;
            break;
        case 17:
            //Read Port
            dR=PORTBbits.RB11;
            //Return Variable
            return dR;
            break;
        case 18:
            //Read Port
            dR=PORTBbits.RB12;
            //Return Variable
            return dR;
            break;
        case 19:
            //Read Port
            dR=PORTBbits.RB13;
            //Return Variable
            return dR;
            break;
        case 20:
            //Read Port
            dR=PORTBbits.RB14;
            //Return Variable
            return dR;
            break;
        case 21:
            //Read Port
            dR=PORTBbits.RB15;
            //Return Variable
            return dR;
            break;
        default:
            return false;
            break;
    }
}


/*--------------------------------------
 test harness function to test pinMode()
 and digitalRead()
 --------------------------------------*/
#if 0
#define TSW                 PORTAbits.RA0 
//mode pin to allow testing and force test harness to proceed to next pin


int main(void) 
{
    //Configure all ports to digital
    digiPin();
    
    /*-----------------------------------
     * Configure all ports to inputs in
     * order to test functions
     * ---------------------------------*/
    TRISA = 1;
    TRISB = 1;
    pinMode(RB15,0);
    pinMode(RA0,1);    //port RB15 set to output to allow measurement changes
                       //when manipulating variables; RA0 is input for switch
    //Infinite loop since microprocessor cannot return anywhere
    while(1)
    {
        /*-------------------------------------------------------------------
         Write 0 to all ports to begin event checking event with known value
         and test digital read function
         -------------------------------------------------------------------*/
        LATA = 0;
        LATB = 0;
        //Event checking for loop variable declaration
        static int i = 2;
        static int j;
        
        while (i <= 20) //While loop to cycle through every pin 
        {
            //Implement digitalRead() and check if it matches input manually            

                LATBbits.LATB15=digitalRead(i);

                if (TSW == 1)
                {
                    i++; //touch sensor input increment i 
                    // to proceed to next pin
                    for(j=1;j<1000000;j++){} //delay for touch sensor
                }

        }
    }

}
#endif

/*--------------------------------------
 test harness function to test pinMode()
 and digitalWrite()
 --------------------------------------*/
#if 0
#define TSW                 PORTAbits.RA0 
//mode pin to allow testing and force test harness to proceed to next pin


int main(void) 
{
    //Configure all ports to digital
    digiPin();
    
    /*-----------------------------------
     * Configure all ports to output in
     * order to test functions
     * ---------------------------------*/
    TRISA = 0;
    TRISB = 0;
    pinMode(RB15,1);
    pinMode(RA0,1);    //port RB15 set to input to allow measurement changes
                       //when manipulating variables; RA0 is input for switch
    //Infinite loop since microprocessor cannot return anywhere
    while(1)
    {
        /*-------------------------------------------------------------------
         Write 0 to all ports to begin event checking event with known value
         and test digital read and digital write functions
         -------------------------------------------------------------------*/
        LATA = 0;
        LATB = 0;
        
        //Event checking for loop variable declaration
        static int i = 2;
        static int j;
        
        while (i <= 20) //While loop to cycle through every pin
        {
            //Implement digitalWrite() and set value to high, allowing to see a difference
            //from initialization value of all ports, then set to low to see a peak.
            
                digitalWrite(i, PORTBbits.RB15);
                for(j=1;j<100000;j++){} // delay for loop
                digitalWrite(i, 0);
                if (TSW == 1)
                {
                    i++; //touch sensor input increment i 
                    // to proceed to next pin
                    for(j=1;j<10000000;j++){}
                }

        }
    }

}
#endif