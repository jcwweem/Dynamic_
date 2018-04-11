/*
 * measurement.c
 *
 *  Created on: Mar 16, 2018
 *      Author: Joep van de Weem
 *
 */

#include "measurement.h"

uint16_t measureCel(uint16_t celNr){
	uint16_t* startPoint = getPrevMPPVoltage(celNr); // get the value that was optimal for the previous measurement

//	SHIFT_startCelMeasurement(celNr);

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

	if(*startPoint >= 0xFFF){
		*startPoint = 0xFFE;
	}

	return prevValue; 						 		//returns the cel's pp
}

void initMeasurement(void){
	ADC_initialiseADC();								//initializes the ADC
	DAC_initialiseDAC();								//initializes the DAC
//	initialiseShiftReg();							//initializes the Shift Register
	nrOfCells = measureNrOfCells();					//gets the number of cells that are currently connected in the array
}

uint16_t measureNrOfCells(){
	uint16_t measurement;
	for (int i = 0; i < maxNrOfCells; i++)
	{
		measurement = measureCel(i);				//measures the cell
		if(measurement <= referenceValue)			//if the value is less then the lowest value possible
		{
			return i;								//return the current index
		}
	}
	return maxNrOfCells;
}

uint16_t measurePoint(uint16_t voltage){
	DAC_setDAC(voltage);								//set the output voltage for the DAC
	uint16_t current;
	ADC_getADC(&voltage, &current, 0);						//get the voltage and current measurements
	return (voltage * current);						//return the power.
}

uint16_t measureString(uint16_t stringNr){
	DAC_setDAC(0);

//	SHIFT_startStringMeasurement(stringNr);

	uint16_t voltage;
	ADC_getADC(0, 0, &voltage);							//measures the voltage
	return voltage;									//returns the measured voltage
}

uint16_t* getPrevMPPVoltage(uint16_t celNr){
	static uint16_t prevMPPVoltage[maxNrOfCells];	//sets the number of cells
	return &prevMPPVoltage[celNr];					//returns the address for the previous voltage
}

void startMeasurement(uint16_t celNr){
	uint16_t measurement[nrOfCells];				//makes an array with the maximum number of cells
	for (int i = 0; i <= nrOfCells; i++)
	{
		measurement[i] = measureCel(i);				//measures each cell and puts the value in the array
	}
//	SHIFT_stopcellmeasurement();					//stops the cell measurement, i dont know if this is needed
	passMeasurement(measurement);					//passes the measurement
}

void passMeasurement(uint16_t* results){
	//undefinedfunction(results);
}
