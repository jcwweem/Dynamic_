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

uint32_t a, b, c;

int main(void)
{
	HAL_Init(); 				//initialises the HAL

	SystemClock_Config();		//initialises the Clock

	gpio_initialiseGPIO();		//initialises the GPIO
	DAC_initialiseDAC();		//initialises the DAC
	ADC_initialiseADC();		//initialises the ADC

	while(1)
	{

	}

}
