#include <stdio.h>
#include <stdbool.h>
#include <locale.h>

#define SIZE sizeof(int) * 8

void dec2bin(int number, bool *bin)
{
	for (int i = 0; i < SIZE; i++)
	{
		bin[i] = (number & 1) == 1;
		number >>= 1;
	}
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

void sumBinary(bool* binA, bool* binB, bool* binResult)
{
	bool memory = false;

	for (int i = 0; i < SIZE; i++)
	{
		int sum = binA[i] + binB[i] + memory;
		binResult[i] = sum == 1 || sum == 3;
		memory = sum == 3 || sum == 2;
	}
}

bool testSumBinary()
{
	for (int a = 0; a < 1000; a++)
	{
		for (int b = 0; b < 1000; b++)
		{
			int actualSum = a + b;
			bool binA[SIZE];
			bool binB[SIZE];
			bool binResult[SIZE];
			dec2bin(a, binA);
			dec2bin(b, binB);
			sumBinary(binA, binB, binResult);
			int givenSum = bin2dec(binResult);

			if (actualSum != givenSum)
			{
				return false;
			}
		}
	}
	return true;
}

int main()
{
	if (!testSumBinary())
	{
		printf("Test failed!");
		return;
	}
	
	int a = 5;
	int b = -13;
	int result;
	bool binA[SIZE];
	bool binB[SIZE];
	bool binResult[SIZE];

	dec2bin(a, binA);
	dec2bin(b, binB);
	sumBinary(binA, binB, binResult);
	result = bin2dec(binResult);

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
}