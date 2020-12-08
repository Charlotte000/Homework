#define _CRT_SECURE_NO_WARNINGS

#include "HashTable.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

char* readFile(char* fileName)
{
	char* string = calloc(666, sizeof(char));
	if (string == NULL)
	{
		return NULL;
	}

	int index = 0;
	FILE* file = fopen(fileName, "r");
	while (!feof(file))
	{
		char character = ' ';
		fscanf(file, "%c", &character);
		string[index++] = character;
	}
	string[index++] = '\0';

	fclose(file);
	return string;
}

char* process(char* input)
{
	char* output = calloc(666, sizeof(char));
	if (output == NULL)
	{
		return NULL;
	}

	int indexI = 0;
	HashTable* hash = createTable();

	while (input[indexI] != '\0')
	{
		char character = input[indexI++];
		int oldValue = popValue(hash, character);
		pushValue(hash, character, oldValue + 1);
	}

	indexI = 0;
	int indexO = 0;
	while (input[indexI] != '\0')
	{
		char character = input[indexI++];
		if (getValue(hash, character) == 1)
		{
			output[indexO++] = character;
		}
	}
	output[indexO++] = '\0';

	deleteHash(&hash);
	return output;
}

bool test(void)
{
	bool isPassed = true;
	isPassed = isPassed && strcmp(process("hello world!"), "he wrd!") == 0;
	isPassed = isPassed && strcmp(process("haha"), "") == 0;
	isPassed = isPassed && strcmp(process(""), "") == 0;
	isPassed = isPassed && strcmp(process("abc\ndef"), "abc\ndef") == 0;
	return isPassed;
}

int main()
{
	if (!test())
	{
		printf("Test Failed!\n");
		return;
	}

	HashTable* table = createTable();
	char* input = readFile("data.txt");
	char* output = process(input);
	printf("%s", output);

	free(input);
	free(output);
}