#ifndef PORTMAP_H
#define	PORTMAP_H

//Other header files 
#include <stdint.h>
#include <stdbool.h>

//TypeDef for mapping ports to integer pin
typedef enum
{
    RA0 = 1,
    RA1,
    RA2,
    RA3,
    RA4,
    RB0,
    RB1,
    RB2,
    RB3,
    RB4,
    RB5, 
    RB6, 
    RB7, 
    RB8, 
    RB9, 
    RB10, 
    RB11, 
    RB12, 
    RB13, 
    RB14, 
    RB15,    
}pin_t;

typedef enum
{
   LOW = 0,
   HIGH = 1,
}HL_t;

typedef enum
{
   OUTPUT = 0,
   INPUT = 1,
}IO_t;

//Pin Function Prototypes
void digiPin(void);
bool pinMode(pin_t pin, IO_t IO);
bool digitalWrite(pin_t pin, HL_t HL);
uint8_t digitalRead(pin_t pin);

//SPI Function Prototypes
bool spi_Init(uint8_t bit_width, uint16_t BRG_Decimal);
bool spi_Write(uint32_t data);
uint8_t spi_NumBufXMITspace_available(void);
bool spi_XMITBUF_available(void);
bool spi_srXFERcomplete(void);

//dotStar Function Prototypes
bool dotStar_Init(void);
bool dotStar_Write(uint8_t Bright1, uint8_t Red1, uint8_t Blue1, uint8_t Green1, uint8_t Bright2, uint8_t Red2, uint8_t Blue2, uint8_t Green2);

#endif	/* PORTMAP_H */

