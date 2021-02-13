#define _CRT_SECURE_NO_WARNINGS

#include "HashTable.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int hashFunction(char* string, int tableSize)
{
	int result = 0;
	for (size_t i = 0; i < strlen(string); i++)
	{
		result = (result + (int)string[i]) % tableSize;
	}
	return result;
}

HashTable* readFile(void)
{
	HashTable* table = createTable(&hashFunction);

	char* string = malloc(sizeof(char) * 100);
	if (string == NULL)
	{
		return;
	}
	FILE* file = fopen("data.txt", "r");

	while (!feof(file))
	{
		fscanf(file, "%s", string);
		int prevValue = getValue(table, string);
		pushValue(table, string, prevValue + 1);
	}
	free(string);
	fclose(file);
	return table;
}

void printFrequencies(HashTable* table)
{
	for (int i = 0; i < table->maxSize; i++)
	{
		Data* cursor = table->table[i];
		while (cursor != NULL)
		{
			printf("%10s - %d\n", cursor->key, cursor->value);
			cursor = cursor->next;
		}
	}
}

float getFillFactor(HashTable* table)
{
	int count = 0;
	for (int i = 0; i < table->maxSize; i++)
	{
		if (table->table[i] != NULL)
		{
			count++;
		}
	}
	return (float)count / table->maxSize;
}

void maxAverageListLength(HashTable* table, int* maxLength, float* averageLength)
{
	*maxLength = 0;
	int listCount = 0;
	int sumLength = 0;
	for (int i = 0; i < table->maxSize; i++)
	{
		int currentLength = 0;
		Data* cursor = table->table[i];
		if (cursor != NULL)
		{
			listCount++;
		}
		while (cursor != NULL)
		{
			cursor = cursor->next;
			currentLength++;
		}
		*maxLength = *maxLength < currentLength ? currentLength : *maxLength;
		sumLength += currentLength;
	}
	*averageLength = (float)sumLength / listCount;
}

bool test(void)
{
	bool isPassed = true;
	HashTable* table = createTable(&hashFunction);
	isPassed = isPassed && popValue(table, "blabla") == NULL;
	isPassed = isPassed && getValue(table, "blabla") == NULL;
	pushValue(table, "test", 123);
	isPassed = isPassed && getValue(table, "test") == 123;
	isPassed = isPassed && popValue(table, "test") == 123;
	deleteHash(&table);
	isPassed = isPassed && table == NULL;
	return isPassed;
}

int main()
{
	if (!test())
	{
		printf("Test failed!\n");
		return;
	}

	HashTable* table = readFile();

	printFrequencies(table);
	printf("Fill factor: %.2f\n", getFillFactor(table));

	int maxLength = 0;
	float averageLength = .0;
	maxAverageListLength(table, &maxLength, &averageLength);
	printf("Max list length: %d\n", maxLength);
	printf("Average list length: %.3f\n", averageLength);

	deleteHash(&table);
}