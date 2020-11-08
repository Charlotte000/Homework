#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include "Sort.h"

int getMostFrequent(int* items, int arraySize)
{
	quickSort(items, 0, arraySize - 1);

	int maxCount = 0;
	int maxValue = items[0];
	int currentCount = 0;
	for (int i = 1; i < arraySize; i++)
	{
		if (items[i] == items[i - 1])
		{
			currentCount++;
			if (maxCount < currentCount)
			{
				maxValue = items[i];
				maxCount = currentCount;
			}
		}
		else {
			currentCount = 0;
		}
	}
	return maxValue;
}

int getNumberOfItems(FILE* file)
{
	int arraySize = 0;
	while (!feof(file))
	{
		fscanf(file, "%*d");
		arraySize++;
	}
	rewind(file);
	return arraySize;
}

int* countCharacters(FILE* file, int arraySize)
{
	int* items = malloc(sizeof(int) * arraySize);
	if (items == NULL)
	{
		printf("Failed. Try again");
		return NULL;
	}

	int index = arraySize - 1;
	while (!feof(file))
	{
		int number = 0;
		fscanf(file, "%d", &number);
		items[index] = number;
		index--;
	}
	rewind(file);
	return items;
}

bool test(void)
{
	bool isPassed = true;

	int numbers1[5] = { 0, 1, 2, 0, 0 };
	isPassed = isPassed && getMostFrequent(numbers1, 5) == 0;
	int numbers2[5] = { 1, 4, 1, 3, 5 };
	isPassed = isPassed && getMostFrequent(numbers2, 5) == 1;
	return isPassed;
}

int main()
{
	setlocale(LC_ALL, "Russian");

	if (!test())
	{
		printf("Test failed");
		return;
	}

	// Read file
	FILE* file = fopen("data4.2.txt", "r");
	if (file == NULL)
	{
		printf("File not Found");
		return;
	}

	int arraySize = getNumberOfItems(file);
	int* items = countCharacters(file, arraySize);
	if (items != NULL)
	{
		int maxValue = getMostFrequent(items, arraySize);
		printf("Самый частый элемент: %d\n", maxValue);
		free(items);
	}
	else
	{
		printf("Error. Try again");
	}
	fclose(file);
}