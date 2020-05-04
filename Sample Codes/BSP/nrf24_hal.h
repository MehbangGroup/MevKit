#ifndef __NRF24_HAL_H
#define __NRF24_HAL_H

// Peripheral libraries
#include "stm32f1xx_hal.h"
#include "spi.h"

// CE (chip enable) pin
#define nRF24_CE_L()               HAL_GPIO_WritePin(CE_GPIO_Port, CE_Pin, GPIO_PIN_RESET)
#define nRF24_CE_H()               HAL_GPIO_WritePin(CE_GPIO_Port, CE_Pin, GPIO_PIN_SET)

// CSN (chip select negative) pin
#define nRF24_CSN_L()              HAL_GPIO_WritePin(CSN_GPIO_Port, CSN_Pin, GPIO_PIN_RESET)
#define nRF24_CSN_H()              HAL_GPIO_WritePin(CSN_GPIO_Port, CSN_Pin, GPIO_PIN_SET)

// Function prototypes
uint8_t nRF24_LL_RW(uint8_t data);

#endif // __NRF24_HAL_H
