#include "../u8g2Headers/SPI_master.h"
 //tweaked for PIC32MX170F256B, uses SPI2
         

/****************************************************************************
 Function
    SPI_Init_Display
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
void SPI_Init_Display(void){
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
    SPI_Init_Dotstar
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
void SPI_Init_Dotstar(void){
    //disable analog function on all SPI pins
    ANSELBbits.ANSB15 = 0;             //Set RB15 as analog
    TRISBbits.TRISB5 = 0;              //Set RB5 as output
    TRISBbits.TRISB15 = 0;             //Set RB15 as output
    // Set up PPS
    RPA3R = 0b0100;                    // Set RA3 as SS2
    RPB5R = 0b0100;                    // Set RB5 as SDO2
    // Turn off SPI
    SPI2CONbits.ON = 0;
    // Clear Rx buffer
    uint32_t clearbuff = SPI2BUF;
    // Set Baud Rate  
    SPI2BRG = 0;
    // Micro Settings
    SPI2CONbits.ENHBUF = 1;             // Turn on enhanced buffer
    SPI2STATbits.SPIROV = 0;            // Clear SPIROV bit. 
    SPI2CONbits.MSTEN = 1;              // Set PIC32 as master.
    // Set bit width
    SPI2CONbits.MODE32 = 1;
    SPI2CONbits.MODE16 = 1;
    // Clock Settings
    SPI2CONbits.MCLKSEL = 0;            // Set MCLK as PBCLK
    SPI2CONbits.CKE = 0;                // Set CKE as 0 (second edge active)
    SPI2CONbits.CKP = 1;                // Set CKP as 1 (idle state is high)
    // SS Settings
    SPI2CONbits.SSEN = 1;               // SS is slave select
    SPI2CONbits.FRMPOL = 0;             // SS is active low
    SPI2CONbits.MSSEN = 1;              // SS automatically controlled
    // Turn on SPI 
    SPI2CONbits.ON = 1;
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
   bool buffer_full = SPI2STATbits.SPITBF;
   while (buffer_full){
      buffer_full = SPI2STATbits.SPITBF;
   }
   SPI2BUF = data;
   // Read buffer to prevent overruns
   uint8_t clear_var = SPI2BUF;
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
   for (uint8_t i = 0; i < length; i++){
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
    //check that transmit buffer is not full
    if(!SPI2STATbits.SPITBF){
        //split up value based on bitWidth and write to SPI
         SPI2BUF = value; //write to SPI
         returnVal = true; //write is successful!
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
    static uint8_t last_state = 1;
    uint8_t current_state = SPI2STATbits.SRMT;
    bool event_occurred;
    if((current_state != last_state) && (current_state == 0)){
        event_occurred = true;
    } else {
        event_occurred = false;
    }
    last_state = current_state;
    return event_occurred;
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
    static uint8_t last_state = 1;
    uint8_t current_state = SPI2STATbits.SPITBF;
    bool event_occurred;
    if((current_state != last_state) && (current_state == 0)){
        event_occurred = true;
    } else {
        event_occurred = false;
    }
    last_state = current_state;
    return event_occurred;
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
    return (128 / 32) - SPI2STATbits.TXBUFELM;
}
