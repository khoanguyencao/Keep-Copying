#include "../u8g2Headers/spi_master.h"
 //tweaked for PIC32MX170F256B, uses SPI1
         
/****************************************************************************
 Function
    SPI_Init
 Parameters
    void
 Returns
    void
 Description
    set up the SPI system for use. Set the clock phase and polarity, master mode
    clock source, baud rate, SS control, transfer width (8-bits)
 Notes
    don't forget to map the pins & set up the TRIS not only for the SPI pins
    but also for the DC (RB13) & Reset (RB12) pins 
 
****************************************************************************/
void SPI_Init(void){
    uint8_t clearbuff;
    
    //disable analog function on all SPI pins
    ANSELAbits.ANSA0 = 0;   //RA0
    ANSELAbits.ANSA1 = 0;   //RA1
    ANSELBbits.ANSB12 = 0;  //RB12
    ANSELBbits.ANSB13 = 0;  //RB13
    ANSELBbits.ANSB14 = 0;  //RB14
    
    //set RA0 to output and SS*
    TRISAbits.TRISA0 = 0;
    RPA0R = 0b0011;
    
    //set RA1 to output and SDO
    TRISAbits.TRISA1 = 0;
    RPA1R = 0b0011;
    
    //set RB12, RB13, RB14 to output
    TRISBbits.TRISB12 = 0; //reset line
    TRISBbits.TRISB13 = 0; //data command line
    TRISBbits.TRISB14 = 0; //clock line
    
    //stop and reset SPI module by clearing the ON bit
    SPI1CONbits.ON = 0;
    
    //clear the receive buffer
    clearbuff = SPI1BUF;
    
    //turn off enhanced buffer mode
    SPI1CONbits.ENHBUF = 0;

    //write the baud rate register (999 when validating and 0 when done)
    //SPI1BRG = 999;
    SPI1BRG = 0;

    //clear the SPIROV bit
    SPI1STATbits.SPIROV = 0;
    
    //write desired settings
    SPI1CONbits.MODE32 = 0; //turn on 8 bit transfer mode
    SPI1CONbits.MODE16 = 0; //turn on 8 bit transfer mode
    SPI1CONbits.CKE = 0; //set 2nd clock edge as active
    SPI1CONbits.CKP = 1; //set clock idle high
    SPI1CONbits.MSTEN = 1; //enable master mode
    SPI1CONbits.MSSEN = 1; //slave select enabled
    SPI1CONbits.MCLKSEL = 0; //set MCLK as peripheral bus CLK
    SPI1CONbits.SMP = 0; //input data sampled at middle of data output time
    SPI1CONbits.FRMPOL = 0; //frame pulse or SS pin is active low
    SPI1CONbits.FRMEN = 0; //framed SPI support is disabled
    SPI1CONbits.DISSDI = 0; //SDI pin controlled by SPI module
    
    //enable SPI operation by setting th ON bit
    SPI1CONbits.ON = 1;   
}
/****************************************************************************
 Function
    SPI_Tx
 Parameters
   uint8_t data   the 8-bit value to be sent out through the SPI
 Returns
    void
 Description
    write the data to the SPIxBUF and then wait for it to go out (SPITBF)
 Notes
    don't forget to read the buffer after the transfer to prevent over-runs
 
****************************************************************************/
void SPI_Tx(uint8_t data){
   bool buffer_full;
   buffer_full = SPI1STATbits.SPITBF;
   while (buffer_full){
      buffer_full = SPI1STATbits.SPITBF;
   }
   SPI1BUF = data;
   // Read buffer to prevent overruns
   uint8_t clear_var;
   clear_var = SPI1BUF;
}

/****************************************************************************
 Function
    SPI_TxBuffer
 Parameters
   uint8_t *buffer, a pointer to the buffer to be transmitted 
   uint8_t length   the number of bytes in the buffer to transmit
 Returns
    void
 Description
   loop through buffer calling SPI_Tx for each element in the buffer
 Notes

 
****************************************************************************/
void SPI_TxBuffer(uint8_t *buffer, uint8_t length){
   uint8_t i;
   for (i = 0; i < length; i++){
      SPI_Tx(buffer[i]);
   }
}

/****************************************************************************
 Function
    SPI_Write
 Parameters
   uint32_t value
 Returns
    bool
 Description
    write to SPI buffer
 Notes
****************************************************************************/
bool SPI_Write(uint32_t value){
    bool returnVal = false;
    uint8_t bitWidth;
    
    //check what bitWidth is
    if (SPI1CONbits.MODE32 == 1){
        bitWidth = 32;
    }
    else if (SPI1CONbits.MODE16 == 1){
        bitWidth = 16;
    }
    else if (SPI1CONbits.MODE32 == 0 & SPI1CONbits.MODE16 == 0){
        bitWidth = 8;
    }
    
    //check that transmit buffer is not full
    if(!SPI1STATbits.SPITBF){
        //split up value based on bitWidth and write to SPI
        if (bitWidth == 32){
            SPI1BUF = value; //write to SPI
            returnVal = true; //write is successful!
        }
        else if (bitWidth == 16){
            //create two variables to store 16 bit words
            uint16_t value1;
            uint16_t value2;

            //set variables to each 16 bit segment
            value1 = value & 0x00FF;
            value2 = value >> 16;

            //write to SPI
            SPI1BUF = value1;
            SPI1BUF = value2;

            returnVal = true; //write is successful!
        }
        else if (bitWidth == 8){
            //create four variables to store 8 bit words
            uint8_t value1;
            uint8_t value2;
            uint8_t value3;
            uint8_t value4;

            //set variables to each 8 bit segment
            value1 = value & 0x00FF;
            value2 = value >> 8;
            value3 = value >> 16;
            value4 = value >> 24;

            //write to SPI
            SPI1BUF = value1;
            SPI1BUF = value2;
            SPI1BUF = value3;
            SPI1BUF = value4;

            returnVal = true; //write is successful!
        } 
    }
    else {
        //transmit buffer must be full
        returnVal = false;
    }
    return returnVal;
}

/****************************************************************************
 Function
    SPI_HasTransferCompleted
 Parameters
    none
 Returns
    bool
 Description
    check if transfer finished
 Notes
****************************************************************************/
bool SPI_HasTransferCompleted(){
    static uint8_t lastRegState = 0; //set to full
    uint8_t currentRegState;
    bool transferComplete;
    
    //set currentState to shift register state
    currentRegState = SPI1STATbits.SRMT;
    if ((lastRegState != currentRegState) && (currentRegState == 1)){
        //the shift register must have become empty
        transferComplete = true;
    }
    else {
        //the shift register must not be empty
        transferComplete = false;
    }
    //set last state equal to current state
    lastRegState = currentRegState;
    return transferComplete;
}

/****************************************************************************
 Function
    SPI_HasXmitBufferSpaceOpened
 Parameters
    none
 Returns
    bool
 Description
    check if a space in buffer is empty
 Notes
****************************************************************************/
bool SPI_HasXmitBufferSpaceOpened(){
    static uint8_t lastBufferState = 1; //set to full
    uint8_t currentBufferState;
    bool spaceOpen;
    
    //set current state to transmit buffer state
    currentBufferState = SPI1STATbits.SPITBF;
    if ((lastBufferState != currentBufferState) && (currentBufferState == 0)){
        //transmit buffer space must not be full
        spaceOpen = true;
    }
    else {
        //transmit buffer space must be full
        spaceOpen = false;
    }
    //set last state equal to current state
    lastBufferState = currentBufferState;
    return spaceOpen;
}

/****************************************************************************
 Function
    SPI_GetNumOpenXmitSpaces
 Parameters
    none
 Returns
    uint8_t 
 Description
    checks how many open spaces there are in the buffer
 Notes
****************************************************************************/
uint8_t SPI_GetNumOpenXmitSpaces(){
    uint8_t numSpaces;
    numSpaces = 4 - SPI1STATbits.TXBUFELM;
    return numSpaces;
}
