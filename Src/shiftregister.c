/*
 * shiftregister.c

 *
 *  Created on: 11 apr. 2018
 *      Author: Joris
 */

#define maxNrOfCells 		64 	//defines the maximum number of cells
#define referenceValue 		120 // defines the value that is measured when no solar panel is connected

#include "shiftregister.h"
#include "gpio.h"
#include "measurement.h"

int amountOfCells = 1;
int* bitsArray;

//initialize shiftregister
void initShiftregister()
{
	//initGpio
	gpio_initialiseGPIO();

	//initCell
//	initAmountOfCells();
	int newbitsArray[amountOfCells];
	bitsArray = & newbitsArray[amountOfCells];

	//fill entire array. Value: 0xFAA(not in circuit)
	for(int i = 0; i < amountOfCells; i++)
	{
		bitsArray[i] = 0xE38;
	}
}

//A test where the given value is passed into all cells
void shift_writeCellsTest(int value)
{
	//set enable to 0
	gpio_setGPIO(PB0, 0);
	delay();

	//write all cells
	for(int i = 0; i < amountOfCells; i++)
	{
		shift1Cell(value);
	}

	//set enable to 1
	gpio_setGPIO(PB0, 1);
	delay();

	//set enable to 0
	gpio_setGPIO(PB0, 0);
	delay();
}

//measures all cells and returns an int array
void measureAllCells(int* array)
{
	//create a temp array
	int measureArray[amountOfCells];

	//loop through all cells
	for(int i = 0; i < amountOfCells; i++)
	{
		//set this cell to be measured
		shift_measureAt(i);

		//measure cell and add it to array
		measureArray[i] = measureCel(i);
	}

	//update array with temparray
	array = measureArray;

	//put circuit back in old state
	shift_measureAt(100000); //by setting this to an insane amount the circuit is put back together
}

//measure at 1 cell, the one measured is given by index
void shift_measureAt(int index)
{
	//amount of cells x 12
	for(int i = amountOfCells; i > 0; i--)
	{
		if(i == index)
		{
			//put cell on measureline
			shift1Cell(0x0AA);
		}
		else
		{
			//keep cell in same state
			shift1Cell(bitsArray[i]);
		}
	}
}

//shift 1 cell(12bits) into the shift register, value is a hexadecimal number
void shift1Cell(int value)
{
	//shift 12bits
	for(int i = 0; i < 12; i++)
	{
		//select bit to be shifted
		shift1Bit((((0x1 << i)) & value) >> i);
	}
}

//shift 1 bit into shift register
void shift1Bit(int bit)
{
	//make sure clock is low
	gpio_setGPIO(PB7, 0);
	delay();
	//set Data
	gpio_setGPIO(PB6, bit);
	delay();
	//clock pulse
	gpio_setGPIO(PB7, 1);
	delay();
	//make sure clock is low again
	gpio_setGPIO(PB7, 0);
	delay();
}

//initialises the amount of cells present in our circuit
void initAmountOfCells()
{
	for (int i = 0; i < maxNrOfCells; i++)
		{
			//measures the cell
			if(measureCel(i) <= referenceValue)			//if the value is less then the lowest value possible
			{
				amountOfCells = i+1;					//return the current index
			}
		}
}

//delay function
void delay()
{
	for(int i = 0; i<40000; i++)
	{
		asm("NOP");
	}
}


/*
 * Waarde van integers die gestuurd moeten worden bij bepaalde acties:
 *
 * Cell naar lijn 1:
 * 		1111 1010 1001		0xFA9
 *
 * Cell naar lijn 2:
 * 		1111 1010 0110		0xFA6
 *
 * Cell naar lijn 3:
 * 		1111 1001 1010		0xF9A
 *
 * Cell naar lijn 4:
 * 		1111 0110 1010		0xF6A
 *
 * Cell meten:
 * 		0000 1010 1010		0x0AA
 *
 * Cell los:
 * 		1111 1010 1010		0xFAA
 *
 */
