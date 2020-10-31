#include "../u8g2Headers/SPI_master.h"
 //tweaked for PIC32MX170F256B, uses SPI2
         
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
    if((current_state != last_state) && (current_state == 1)){
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
    static uint8_t last_state = 0;
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
