/*
 * adc.h
 *
 *  Created on: Mar 29, 2018
 *      Author: Joep van de Weem
 */

#ifndef ADC_H_
#define ADC_H_


#include "stm32l4xx_hal.h"


ADC_HandleTypeDef hadc1;

/*
 * initialises the ADC
 */
void ADC_initialiseADC();

/*
 * gets the voltage and current of a single cell.
 * @param voltage of a single cell, current of a single cell
 */
void ADC_getADC(uint32_t* channel1, uint32_t* channel2, uint32_t* channel3);


#endif /* ADC_H_ */
