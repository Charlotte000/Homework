#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <locale.h>
#include "Header.h"

int main()
{
	// ==Read file==
	FILE* file = fopen("data4.2.txt", "r");
	if (file == NULL)
	{
		printf("File not Found");
		return;
	}

	// Get number of items
	int arraySize = 0;
	while (!feof(file))
	{
		int number;
		fscanf(file, "%d", &number);
		arraySize++;
	}
	rewind(file);

	// Create array
	int* items = malloc(sizeof(int) * arraySize);
	if (items == NULL)
	{
		printf("Failed. Try again");
		return;
	}

	// Fill array
	int index = 0;
	while (!feof(file))
	{
		int number;
		fscanf(file, "%d", &number);
		items[index] = number;
		index++;
	}
	fclose(file);

	// Sort
	quickSort(items, 0, arraySize - 1);

	// Сalculate the most frequent element
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

	// Print
	setlocale(LC_ALL, "Russian");
	printf("Самый частый элемент: %d\nКоличество данного элемента: %d\n", maxValue, maxCount + 1);

}