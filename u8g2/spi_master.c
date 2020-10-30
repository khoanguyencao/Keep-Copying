#include "../u8g2Headers/spi_master.h"
#include "../u8g2Headers/portmap.h"
 //tweaked for PIC32MX170F256B, uses SPI1


static uint8_t rBUF_Data;

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
        //setting all pins to digital
    digiPin();
    
    //Set pins RA0, RA1, RB12, RB13, and RB14 to output with TRIS
    pinMode(RA0, OUTPUT); pinMode(RA1, OUTPUT); pinMode(RB14, OUTPUT);
    pinMode(RB12, OUTPUT); pinMode(RB13, OUTPUT);
      
    //Map RA0 to SS output, RA1 to SDO output, RB14 to SCK output
    RPA0R=0b0011; RPA1R=0b0011; //RPB14R is always SDK
    
    //Stopping SPI to modify operations
    SPI1CONbits.ON=0;
    SPI1CON2=0;
    
    //Read SPI1BUF to clear receive buffer
    rBUF_Data = SPI1BUF;
    
    //Clear Overflow
    SPI1STATbits.SPIROV=0;
    
    //SET Baud Rate Generator XFER speed of 10MHz
    SPI1BRG = 0;
    
    /*--------------------------------------------------------------------------
    Enable desired Settings: MSSEN, MSTEN, ENHBUF, DISSDO, DISSDI, CKP =1
    SeCKE, FRMPOL =0
     -------------------------------------------------------------------------*/
    SPI1CONbits.CKE =0;
    SPI1CONbits.CKP=1;
    SPI1CONbits.MSTEN=1;
    SPI1CONbits.MSSEN=1;
    SPI1CONbits.ENHBUF=0;
    SPI1CONbits.DISSDO=0;
    SPI1CONbits.FRMPOL=0;
    SPI1CONbits.DISSDI=0;
    
    //Set Bit width XFER rate
            SPI1CONbits.MODE16=0;
            SPI1CONbits.MODE32=0;
     
    //Re-enable SPI functionality
    SPI1CONbits.ON=1;
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
            
            /*-----------------------------------------------------------------
             Write to buffer passing 8 bits at a time and verifying that there
             is open space in the XMIT register before passing the next value
            -----------------------------------------------------------------*/
                SPI1BUF=data;
            //Loop to ensure data has transmitted
                while(SPI1STATbits.SPITBF==1){}
            //Reading buffer to clear it
                rBUF_Data = SPI1BUF;
            
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
//Loop for calling SPI_Tx and counter variable initialization
    int i; //counter
    for(i=0;i<=(length - 1);i++)
    {
        SPI_Tx(*(buffer+i)); //Writing pointer to buffer
    }
}
