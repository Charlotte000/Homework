#define _CRT_SECURE_NO_WARNINGS

#include "IsFloat.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool test(void)
{
	bool isPassed = true;
	isPassed = isPassed && !isFloat("");
	isPassed = isPassed && !isFloat("123");
	isPassed = isPassed && isFloat("123e-12");
	isPassed = isPassed && isFloat("123.0012");
	isPassed = isPassed && isFloat("123,012");
	isPassed = isPassed && !isFloat("123e-12.165");
	isPassed = isPassed && !isFloat("abcdef");
	isPassed = isPassed && !isFloat("123.");
	isPassed = isPassed && !isFloat("123E");
	isPassed = isPassed && !isFloat("e123");
	return isPassed;
}

int main()
{
	if (!test())
	{
		printf("Test Failed!\n");
		return;
	}

	char* string = calloc(100, sizeof(char));
	if (string == NULL)
	{
		return;
	}
	printf("Input string: ");
	scanf("%s", string);
	printf(isFloat(string) ? "Yes" : "No");
	free(string);
}