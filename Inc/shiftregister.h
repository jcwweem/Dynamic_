/*
 * shiftregister.h
 *
 *  Created on: 11 apr. 2018
 *      Author: Joris
 */

#ifndef SHIFTREGISTER_H_
#define SHIFTREGISTER_H_

void initShiftregister();
void shift_writeCellsTest(int value);
void measureAllCells(int* array);
void shift_measureAt(int index);
void shift1Cell(int value);
void shift1Bit(int bit);
void initAmountOfCells();
void delay();

#endif /* SHIFTREGISTER_H_ */
