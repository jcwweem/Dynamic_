/*
 * Header for measurement
 * This software takes care of the measurements
 */

#ifndef MEASUREMENT_H_
#define MEASUREMENT_H_
// 		Includes

#include "stm32l4xx_hal.h"
#include "adc.h"
#include "dac.h"



#define maxNrOfCells 		64 	//defines the maximum number of cells
#define referenceValue 		120 // defines the value that is measured when no solar panel is connected

uint16_t nrOfCells;		//displays the nr of cells

// 		Public functions
/*
 * initialises the ADC, DAC and variables for measurement.
 */
void initMeasurement(void);

/*
 * starts the measurement of all the cells
 */

// 		Private functions
/*
 * Measures a complete cell and returns the MPP of a given Cel
 */
uint16_t measureCel(uint16_t celNr);

/*
 * measures the PP at a give voltage by reading the ADC for voltage and current
 * @param voltage
 */
uint16_t measurePoint(uint32_t voltage);

/*
 * measures the string
 */
uint16_t measureString();

/*
 * This function returns the voltage that was needed for the previous MPP for a given cel
 * @param celNr
 */
uint16_t* getPrevMPPVoltage(uint16_t celNr); //gets the voltage that was needed for the previous MPP for a given c


#endif
