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

void initShiftregister() //initialize the shiftregister
{
	//initGpio
	gpio_initialiseGPIO();

	//initCell
	initAmountOfCells();
	int newbitsArray[amountOfCells];
	bitsArray = & newbitsArray[amountOfCells];

	for(int i = 0; i < amountOfCells; i++)//fill entire array with zeros // dit moet nog aangepast worden
	{
		bitsArray[i] = 0x0;
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
			shift1Cell(0xF55);
		}
		else
		{
			//keep cell in same state
			shift1Cell(bitsArray[i]);
		}
	}
}

void shift1Cell(int waarde)//als waarde een hexadecimaal getalvan 12 bits
{
	//shift hier 12 bits
	for(int i = 0; i < 12; i++)
	{
		shift1Bit((0x1 << i) && waarde); //select bit to be shifted
	}
}

void shift1Bit(int bit)
{
	//set Data
	gpio_setGPIO("PB6", bit);
	//clock pulse
	gpio_setGPIO("PB7", 1);
	gpio_setGPIO("PB7", 0);
}

void initAmountOfCells()
{
	for (int i = 0; i < maxNrOfCells; i++)
		{
			//measures the cell
			if(measureCel(i) <= referenceValue)			//if the value is less then the lowest value possible
			{
				amountOfCells = i;						//return the current index
			}
		}
}

/*
 * Waarde van integers die gestuurd moeten worden bij bepaalde acties:
 *
 * Cel naar lijn 1:
 * 		000001010110 	0x056
 *
 * Cel naar lijn 2:
 * 		000001011001	0x059
 *
 * Cel naar lijn 3:
 * 		000001100101	0x065
 *
 * Cel naar lijn 4:
 * 		000010010101	0x095
 *
 * Cel meten:
 * 		111101010101	0xF55
 *
 */
 */
