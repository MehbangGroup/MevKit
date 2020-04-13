/* Includes ------------------------------------------------------------------*/
#include "pixel.h"

/* Private functions ---------------------------------------------------------*/
RGB hsv2rgb(HSV in)
{
    float hh, p, q, t, ff;
    int i;
    RGB out;

    if (in.s <= 0.0) // < is bogus, just shuts up warnings
		{
        out.r = in.v;
        out.g = in.v;
        out.b = in.v;
        return out;
    }
		
    hh = in.h;
    if (hh >= 360.0) hh = 0.0;
    hh /= 60.0;
    i = hh;
    ff = hh - i;
    p = in.v * (1.0 - in.s);
    q = in.v * (1.0 - (in.s * ff));
    t = in.v * (1.0 - (in.s * (1.0 - ff)));

    switch (i)
		{
			case 0:
					out.r = in.v;
					out.g = t;
					out.b = p;
					break;
			case 1:
					out.r = q;
					out.g = in.v;
					out.b = p;
					break;
			case 2:
					out.r = p;
					out.g = in.v;
					out.b = t;
					break;

			case 3:
					out.r = p;
					out.g = q;
					out.b = in.v;
					break;
			case 4:
					out.r = t;
					out.g = p;
					out.b = in.v;
					break;
			case 5:
			default:
					out.r = in.v;
					out.g = p;
					out.b = q;
					break;
    }
    return out;
}

/* Exported functions ------------------------------------------------------- */
void PixelInit(void)
{
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);
}

void PixelRGB(RGB color)
{
	TIM3->CCR2 = color.g * 100;
	TIM3->CCR3 = color.b * 100;
	TIM3->CCR4 = color.r * 100;
}

void PixelHSV(HSV color)
{
	RGB rgb = hsv2rgb(color);
	PixelRGB(rgb);
}
