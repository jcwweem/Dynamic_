/*
 * gpio.h
 *
 *  Created on: Apr 11, 2018
 *      Author: Joep van de Weem
 */

#ifndef GPIO_H_
#define GPIO_H_

	#include "stm32l4xx_hal.h"

	/*
	 * Pins
	 */
	enum Pin{PA2, PA5, PA6, PA7, PB0, PB3, PB6, PB7};

	/*
	 *
	 */
	void gpio_initialiseGPIO(void);

	/*
	 *
	 */
	void gpio_setGPIO(enum Pin pinNr, int pinState);

#endif /* GPIO_H_ */
