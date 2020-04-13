/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DISPLAY_H
#define __DISPLAY_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private define ------------------------------------------------------------*/
#define SetCLK  CLK_GPIO_Port->BSRR = CLK_Pin
#define ClrCLK  CLK_GPIO_Port->BRR  = CLK_Pin
#define SetLAT  LAT_GPIO_Port->BSRR = LAT_Pin
#define ClrLAT  LAT_GPIO_Port->BRR  = LAT_Pin
#define SetSDI  SDI_GPIO_Port->BSRR = SDI_Pin
#define ClrSDI  SDI_GPIO_Port->BRR  = SDI_Pin

/* Exported types ------------------------------------------------------------*/
typedef enum
{
  LED_BR, LED_UR, LED_BL, LED_UL
} DISPLAYLED;

/* Exported functions ------------------------------------------------------- */
void DisplayRun(void);
void DisplayLed(int led, int state);
void DisplayString(char* text);

#endif
