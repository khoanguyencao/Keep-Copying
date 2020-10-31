/* 
 * File:   spi_master.h
 * Author: KIKI
 *
 * Created on 2019년 12월 30일 (월), 오후 9:11
 */

#ifndef SPI_MATER_H
#define	SPI_MATERH

#include "../u8g2Headers/u8g2TestHarness_main.h"
#include "../u8g2Headers/common.h"

void SPI_Init(void);
void SPI_Tx(uint8_t data);
void SPI_TxBuffer(uint8_t *buffer, uint8_t length);
bool SPI_Write(uint32_t value);
bool SPI_HasTransferCompleted();
bool SPI_HasXmitBufferSpaceOpened();
uint8_t SPI_GetNumOpenXmitSpaces();

#endif	/* SPI_MATERH */
