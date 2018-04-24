#include <stdio.h>
#include <stdlib.h>

#define maximumperString 32

void fillArray(int *array, int length);
int getRandomNumber();
void printArray(int *array, int length);
void sortArray(int *array, int length);
void amountOfSortedBy10(int *array, int length);

int line1Array[maximumperString];
int line2Array[maximumperString];
int line3Array[maximumperString];
int line4Array[maximumperString];

int line1Filled = 0;
int line2Filled = 0;
int line3Filled = 0;
int line4Filled = 0;

void divideArray(int *array, int length, int range1, int range2, int range3);
void addToLine(int *arrayLine, int *amountInside, int value);
void printLine(int* line);

int main()
{
	int intArray[64];

	time_t t;
	srand((unsigned)time(&t));

	fillArray(&intArray, 64);
//	printArray(&intArray, 64);

	sortArray(&intArray, 64);
//	printArray(&intArray, 64);

	amountOfSortedBy10(&intArray, 64);

	divideArray(&intArray, 64, 75, 50, 25);

	printLine(line1Array);
	printLine(line2Array);
	printLine(line3Array);
	printLine(line4Array);


	while (1)
	{
		
	}

	return 1;
}

void divideArray(int *array, int length, int range1, int range2, int range3) //verdeeld de hele array naar 3 waardes
{
	for (int i = 0; i < length; i++)
	{
		if (array[i] > range1)
		{
			addToLine(&line1Array, &line1Filled, array[i]);
		}
		else if (array[i] > range2)
		{
			addToLine(&line2Array, &line2Filled, array[i]);
		}
		else if (array[i] > range3)
		{
			addToLine(&line3Array, &line3Filled, array[i]);
		}
		else
		{
			addToLine(&line4Array, &line4Filled, array[i]);
		}
	}
}

void addToLine(int *arrayLine, int *amountInside, int value) //simpele add methode(dit kan beter door met arraylists te werken)
{
	arrayLine[*amountInside] = value;
	*amountInside = *amountInside + 1;
}

void printLine(int* line)//print een line
{
	printf("\n");
	for (int i = 0; i < maximumperString; i++)
	{
		if (line[i] == 0)
		{

		}
		else
		{
			printf("%d - ", line[i]);
		}
	}
	printf("\n");
}

void fillArray(int *array, int length)
{
	for (int i = 0; i < length; i++)
	{
		array[i] = getRandomNumber();
	}
}

int getRandomNumber()
{
	return (rand() % 100);
}

void printArray(int *array, int length)
{
	for (int i = 0; i < length; i++)
	{
		printf("%d\n", array[i]);
	}
}

void sortArray(int *array, int length)//bubble
{
	int i, j, temp;
	for (i = 0; i < (length - 1); ++i)
	{
		for (j = 0; j < length - 1 - i; ++j)
		{
			if (array[j] > array[j + 1])
			{
				temp = array[j + 1];
				array[j + 1] = array[j];
				array[j] = temp;
			}
		}
	}
}


void amountOfSortedBy10(int *array, int length)//telt het aantal cellnummers per stap van 10
{
	int waardes[10];
	int counter = 0;

	for (int j = 0; j<10; j++)
	{
		for (int i = 0; i < length; i++)
		{
			if (array[i] >= 90 - (10 * j) && array[i] < 100 - (10 * j))
			{
				counter++;
			}
		}
		waardes[j] = counter;
		counter = 0;
	}

	for (int j = 0; j<10; j++)
	{
		printf("%d waarde: %d -10\n", waardes[j], (100 - (10 *j)));
	}
}