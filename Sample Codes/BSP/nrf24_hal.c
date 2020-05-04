#include "nrf24_hal.h"

// Low level SPI transmit/receive function (hardware depended)
// input:
//   data - value to transmit via SPI
// return: value received from SPI
uint8_t nRF24_LL_RW(uint8_t data)
{
  // transmit/receive function
  uint8_t rx;
  HAL_SPI_TransmitReceive(&hspi2, &data, &rx, 1, 10);

	// Return received byte
	return rx;
}
