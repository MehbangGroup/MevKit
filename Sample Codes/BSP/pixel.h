/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PIXEL_H
#define __PIXEL_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"

/* Exported types ------------------------------------------------------------*/
typedef struct {
    float r;       // a fraction between 0 and 1
    float g;       // a fraction between 0 and 1
    float b;       // a fraction between 0 and 1
} RGB;

typedef struct {
    float h;       // angle in degrees
    float s;       // a fraction between 0 and 1
    float v;       // a fraction between 0 and 1
} HSV;

/* Exported functions ------------------------------------------------------- */
void PixelInit(void);
void PixelRGB(RGB color);
void PixelHSV(HSV color);

#endif
