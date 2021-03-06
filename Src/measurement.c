/*
 * measurement.c
 *
 *  Created on: Mar 16, 2018
 *      Author: Joep van de Weem
 *
 */

#include "measurement.h"

void initMeasurement(void){
	ADC_initialiseADC();							//initializes the ADC
	DAC_initialiseDAC();							//initializes the DAC
}

uint16_t measureCel(uint16_t celNr){
	uint16_t* startPoint = getPrevMPPVoltage(celNr); // get the value that was optimal for the previous measurement

	uint16_t prevValue = measurePoint(*startPoint); //measure the PP for the startpoint

	uint16_t nextValue = measurePoint(*startPoint + 1); //measure the PP for the value that is one bit higher then the previous value
	while(prevValue < nextValue)					//while the previous value is smaller then the new value
	{
		*startPoint = *startPoint + 1; 				//add a voltage to the powerpoint
		prevValue = nextValue; 				  		//the next value is now the previous value
		nextValue = measurePoint(*startPoint + 1);  //the next value is measured by taking a value higher then the previous value.
	}

	nextValue = measurePoint(*startPoint - 1);		//do the same as above but then for the lower voltages
	while(prevValue > nextValue)
	{
		*startPoint = *startPoint - 1;
		prevValue = nextValue;
		nextValue = measurePoint(*startPoint - 1);
	}

	return prevValue; 						 		//returns the cel's pp
}


uint16_t measurePoint(uint32_t voltage){
	DAC_setDAC(voltage);							//set the output voltage for the DAC
	uint32_t current;
	ADC_getADC(&voltage, &current, 0);				//get the voltage and current measurements
	return (voltage * current);						//return the power.
}

uint16_t measureString(){
	DAC_setDAC(0);									//sets the DAC to 0 to prevent he fet from blowing up
	uint32_t voltage;								//sets the voltage
	ADC_getADC(0, 0, &voltage);						//measures the voltage
	return voltage;									//returns the measured voltage
}

uint16_t* getPrevMPPVoltage(uint16_t celNr){
	static uint16_t prevMPPVoltage[maxNrOfCells];	//creates an array
	return &prevMPPVoltage[celNr];					//returns the address for the previous voltage
}
