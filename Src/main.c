/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32l4xx_hal.h"

#include "measurement.h"
#include "gpio.h"
#include "systemClock.h"

#include "shiftregister.h"

uint32_t a, b, c;
void delay();

int main(void)
{
	HAL_Init(); 				//initialises the HAL

	SystemClock_Config();		//initialises the Clock

	gpio_initialiseGPIO();		//initialises the GPIO
	DAC_initialiseDAC();		//initialises the DAC
	ADC_initialiseADC();		//initialises the ADC

	initShiftregister(); 		//initialises the shiftregister

	gpio_setGPIO(PB0, 0);
	shift1Cell(0xFFF);
	gpio_setGPIO(PB0, 1);
//	gpio_setGPIO(PB0, 0);

	while(1)
	{
//		shift1Cell(0xCCC); //1100 1100 1100
//		shift1Cell(0xE38); //1110 0011 1000
		shift_writeCellsTest(0xE38);
//		delay();
//
//		gpio_setGPIO(PB7, 0);
//		delay();
//		gpio_setGPIO(PB7, 1);
//		delay();
//
//		gpio_setGPIO(PB6, 0);
//		delay();
//		gpio_setGPIO(PB6, 1);
//		delay();
	}

}

void delay()
{
	for(int i = 0; i<50000; i++)
	{
		asm("NOP");
	}
}
