#include <stdio.h>
#include <stdbool.h>
#include <locale.h>
#include <stdlib.h>

#define SIZE (sizeof(int) * 8)

bool* dec2bin(int number)
{
	bool *bin = malloc(sizeof(bool) * SIZE);
	if (bin == NULL)
	{
		return NULL;
	}
	for (int i = 0; i < SIZE; i++)
	{
		bin[i] = (number & 1) == 1;
		number >>= 1;
	}
	return bin;
}

int bin2dec(bool* bin)
{
	int number = 0;
	for (int i = 0; i < SIZE; i++)
	{
		if (bin[i])
		{
			number |= 1 << i;
		}
	}
	return number;
}

void printBin(bool* bin)
{
	for (int i = SIZE - 1; i >= 0; i--)
	{
		printf(bin[i] ? "1": "0");
	}
}

bool* sumBinary(bool* binA, bool* binB)
{
	bool* binResult = malloc(sizeof(bool) * SIZE);
	if (binResult == NULL)
	{
		return NULL;
	}
	bool memory = false;

	for (int i = 0; i < SIZE; i++)
	{
		int sum = binA[i] + binB[i] + memory;
		binResult[i] = sum == 1 || sum == 3;
		memory = sum == 3 || sum == 2;
	}
	return binResult;
}

bool testSumBinary()
{
	int testCodes[3][2] = { {123, 123 }, { 0, 0 }, { -147, -741 } };
	bool isPassed = true;

	for (int i = 0; i < 3; i++)
	{
		bool* binA = dec2bin(testCodes[i][0]);
		bool* binB = dec2bin(testCodes[i][1]);
		bool* binResult = sumBinary(binA, binB);
		isPassed = isPassed && bin2dec(binResult) == testCodes[i][0] + testCodes[i][1];
		free(binA);
		free(binB);
		free(binResult);
	}
	return isPassed;
}

int main()
{
	// Test
	if (!testSumBinary())
	{
		printf("Test failed!");
		return;
	}
	
	// Input data
	const int a = 5;
	const int b = -13;
	
	// Convert to binary
	bool* binA = dec2bin(a);
	bool* binB = dec2bin(b);

	// Calculating the sum 
	bool* binResult = sumBinary(binA, binB);
	int result = bin2dec(binResult);

	// Print data
	setlocale(LC_ALL, "Russian");
	printf("%+3d в двоичной системе: ", a);
	printBin(binA);
	printf("\n");
	printf("%+3d в двоичной системе: ", b);
	printBin(binB);
	printf("\n");
	printf("Результат сложения:     ");
	printBin(binResult);
	printf(" = %+3d\n", result);

	// Cleaning
	free(binA);
	free(binB);
	free(binResult);
}