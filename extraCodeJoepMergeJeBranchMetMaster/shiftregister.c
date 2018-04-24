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
	initAmountOfCells();
	int newbitsArray[amountOfCells];
	bitsArray = & newbitsArray[amountOfCells];
	//gpioinit
}

void measureAllCells(int* array) //measure all cells and return an int array
{
	int measureArray[amountOfCells];
	for(int i = 0; i < amountOfCells; i++)
	{
		//select cell(and lines)

			//shift to cell

			//ontkoppel cell
			//meet cell
			//maak cell weer vast

		//measure cell and add it to array
		measureArray[i] = measureCel(i);
	}
	array = measureArray;
}

void shift_measureAt(int index)
{
	//amount of cells x 12
	for(int i = amountOfCells; i > 0; i--)
	{
		if(i == index)
		{
			//put cell on measureline
			shift1Cell(Hier moet value: meetlijn);
		}
		else
		{
			//keep cell in same state
			shift1Cell(Hier moet value: zelfde als ervoor);
		}
	}
}

void shift1Cell(int waarde)//als waarde een struct met 12booleans
{
	//shift hier 12 bits
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
