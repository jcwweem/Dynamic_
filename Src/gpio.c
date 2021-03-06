/*
 * gpio.c
 *
 *  Created on: Apr 11, 2018
 *      Author: Joep van de Weem
 */
#include "gpio.h"


void gpio_initialiseGPIO(void){
	GPIO_InitTypeDef GPIO_InitStruct;

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_3|GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);

	/*Configure GPIO pins : PA0 PA2 PA3 PA4 to be analog pins*/
	GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_3|GPIO_PIN_4;
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/* configure pins PA2 PA5 PA6 PA7 to be GPIO pins */
	GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pins : PB0 PB3 PB6 PB7 */
	GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_3|GPIO_PIN_6|GPIO_PIN_7;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

void gpio_setGPIO(enum Pin pinNr, int pinState){
	switch(pinNr)
	{
		case 0 : //PA2
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, (pinState & 1));
			break;
		case 1 : //PA5
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, (pinState & 1));
			break;
		case 2 : //PA6
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, (pinState & 1));
			break;
		case 3 : //PA7
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, (pinState & 1));
			break;
		case 4 : //PB0
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, (pinState & 1));
			break;
		case 5 : //PB3
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, (pinState & 1));
			break;
		case 6 : //PB6
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, (pinState & 1));
			break;
		case 7 : //PB7
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, (pinState & 1));
			break;
	}
}

