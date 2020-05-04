/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "spi.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "..\..\bsp\nrf24.h"
#include "string.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#undef TRANSMITTER
#undef RECEIVER
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void init_receiver(void)
{
	uint8_t ADDR[] = { 'n', 'R', 'F', '2', '4' }; // the address for RX pipe
	nRF24_DisableAA(0xFF); // disable ShockBurst
	nRF24_SetRFChannel(90); // set RF channel to 2490MHz
	nRF24_SetDataRate(nRF24_DR_2Mbps); // 2Mbit/s data rate
	nRF24_SetCRCScheme(nRF24_CRC_1byte); // 1-byte CRC scheme
	nRF24_SetAddrWidth(5); // address width is 5 bytes
	nRF24_SetAddr(nRF24_PIPE1, ADDR); // program pipe address
	nRF24_SetRXPipe(nRF24_PIPE1, nRF24_AA_OFF, 10); // enable RX pipe#1 with Auto-ACK: disabled, payload length: 10 bytes
	nRF24_SetOperationalMode(nRF24_MODE_RX); // switch transceiver to the RX mode
	nRF24_SetPowerMode(nRF24_PWR_UP); // wake-up transceiver (in case if it sleeping)
}

void receive(void)
{
	uint8_t nRF24_payload[32]; // buffer for payload
	uint8_t payload_length; // variable to store a length of received payload
	uint8_t pipe; // pipe number
	nRF24_RX_ON(); // start receiving
	while (1)
	{
		// constantly poll the status of RX FIFO...
		if (nRF24_GetStatus_RXFIFO() != nRF24_STATUS_RXFIFO_EMPTY)
		{
			// the RX FIFO have some data, take a note what nRF24 can hold up to three payloads of 32 bytes...
			pipe = nRF24_ReadPayload(nRF24_payload, &payload_length); // read a payload to buffer
			nRF24_ClearIRQFlags(); // clear any pending IRQ bits
			if (pipe == nRF24_RX_PIPE1)
				if (!memcmp("HelloWorld", nRF24_payload, payload_length))
					HAL_GPIO_TogglePin(LD6_GPIO_Port, LD6_Pin);
		}
	}
}

void init_transmitter(void)
{
	uint8_t ADDR[] = { 'n', 'R', 'F', '2', '4' }; // the TX address
	nRF24_DisableAA(0xFF); // disable ShockBurst
	nRF24_SetRFChannel(90); // set RF channel to 2490MHz
	nRF24_SetDataRate(nRF24_DR_2Mbps); // 2Mbit/s data rate
	nRF24_SetCRCScheme(nRF24_CRC_1byte); // 1-byte CRC scheme
	nRF24_SetAddrWidth(5); // address width is 5 bytes
	nRF24_SetTXPower(nRF24_TXPWR_0dBm); // configure TX power
	nRF24_SetAddr(nRF24_PIPETX, ADDR); // program TX address
	nRF24_SetOperationalMode(nRF24_MODE_TX); // switch transceiver to the TX mode
	nRF24_SetPowerMode(nRF24_PWR_UP); // wake-up transceiver (in case if it sleeping)
}

void transmit(uint8_t *msg, uint8_t len)
{
	uint8_t status;
	nRF24_CE_L(); // deassert the CE pin (in case if it still high)
	nRF24_WritePayload(msg, len); // transfer payload data to transceiver
	nRF24_CE_H(); // assert CE pin (transmission starts)
	while (1)
	{
		status = nRF24_GetStatus();
		if (status & (nRF24_FLAG_TX_DS | nRF24_FLAG_MAX_RT))
			break; // transmission ended, exit loop
	}
	nRF24_CE_L(); // de-assert CE pin (nRF24 goes to StandBy-I mode)
	nRF24_ClearIRQFlags(); // clear any pending IRQ flags
	// Auto retransmit counter exceeds the programmed maximum limit (payload in FIFO is not removed)
	// Also the software can flush the TX FIFO here...
	if (status & nRF24_FLAG_MAX_RT)
		nRF24_FlushTX();
	// Successful transmission
	if (status & nRF24_FLAG_TX_DS)
		return;
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI2_Init();
  /* USER CODE BEGIN 2 */
	nRF24_Init();
#if defined(TRANSMITTER)
  init_transmitter();
  uint8_t message[] = "HelloWorld";
#elif defined(RECEIVER)
	init_receiver();
  receive();
#endif
  /* USER CODE END 2 */
 
 

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
#if defined(TRANSMITTER)
    transmit(message, sizeof(message));
    HAL_GPIO_TogglePin(LD5_GPIO_Port, LD5_Pin);
    HAL_Delay(500);
#elif defined(RECEIVER)
#else
		if(nRF24_Check())
		{
      HAL_GPIO_TogglePin(LD5_GPIO_Port, LD5_Pin);
      HAL_Delay(500);
		}
#endif
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
