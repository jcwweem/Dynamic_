/*
 * dac.h
 *
 *  Created on: Mar 29, 2018
 *      Author: Joep van de Weem
 */

#ifndef DAC_H_
#define DAC_H_

//	Includes

#include "stm32l4xx_hal.h"


DAC_HandleTypeDef hdac1; //defines the ADC's configs

/*
 * initialises the DAC
 */
void DAC_initialiseDAC();

/*
 * sets the DAC to a certain value
 */
void DAC_setDAC(uint32_t);

#endif /* DAC_H_ */
