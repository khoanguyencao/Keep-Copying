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
   // Pin and PPS Settings
   RPA0R = 0x3;                        // Set RA0 to SS1
   RPA1R = 0x3;                        // Set RA1 to SDO1
   SPI1CONbits.ON = 0;                 // Turn off SPI
   SPI1BRG = 0;                        // Set to 10MHz as required by OLED
   SPI1CONbits.ENHBUF = 0;             // Turn off enhanced buffer
   SPI1STATbits.SPIROV = 0;            // Clear SPIROV bit. 
   SPI1CONbits.MSTEN = 1;              // Set PIC32 as master.
   SPI1CONbits.MODE32 = 0;             // Set bit width to 8 as required by OLED
   SPI1CONbits.MODE16 = 0;
   // Clock Settings
   SPI1CONbits.MCLKSEL = 0;            // Set MCLK as PBCLK
   SPI1CONbits.CKE = 0;                // Set CKE as 0 (second edge active)
   SPI1CONbits.CKP = 1;                // Set CKP as 1 (idle state is high)
   // SS Settings
   SPI1CONbits.SSEN = 1;               // SS is slave select
   SPI1CONbits.FRMPOL = 0;             // SS is active low
   SPI1CONbits.MSSEN = 1;              // SS automatically controlled
   SPI1CONbits.ON = 1;                 // Turn on SPI
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
