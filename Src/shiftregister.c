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

int amountOfCells = 0;
int* bitsArray;

void initShiftregister() //initialize shiftregister
{
	//initGpio
	gpio_initialiseGPIO();

	//initCell
	initAmountOfCells();
	int newbitsArray[amountOfCells];
	bitsArray = & newbitsArray[amountOfCells];

	//fill entire array. Value: 0xFAA(not in circuit)
	for(int i = 0; i < amountOfCells; i++)
	{
		bitsArray[i] = 0xFAA;
	}
}

void measureAllCells(int* array) //measure all cells and return an int array
{
	int measureArray[amountOfCells];
	for(int i = 0; i < amountOfCells; i++)
	{
		//set this cell to be measured
		shift_measureAt(i);

		//measure cell and add it to array
		measureArray[i] = measureCel(i);
	}
	array = measureArray;

	//put circuit back in old state
	shift_measureAt(100000); //by setting this to an insane amount the circuit is put back together
}

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

void shift1Cell(int waarde)//als waarde een hexadecimaal getal van 12 bits
{
	//shift hier 12 bits
	for(int i = 0; i < 12; i++)
	{
		shift1Bit((0x1 << i) && waarde); //select bit to be shifted
	}
}

void shift1Bit(int bit)
{
	//make sure clock is low
	gpio_setGPIO(PB7, 0);
	//set Data
	gpio_setGPIO(PB6, bit);
	//clock pulse
	gpio_setGPIO(PB7, 1);
	gpio_setGPIO(PB7, 0);
}

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
