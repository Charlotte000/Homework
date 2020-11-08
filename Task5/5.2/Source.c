#define _CRT_SECURE_NO_WARNINGS
#include "Stack.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

enum Bracket
{
	ROUND,
	SQUARE,
	CURLY
};

int identifyBracket(char character)
{
	switch (character)
	{
		case '(':
		case ')':
			return ROUND;
		case '{':
		case '}':
			return CURLY;
		case '[':
		case ']':
			return SQUARE;
	}
	return -1;
}

bool checkExpression(char* string)
{
	Stack* stack = createStack();
	for (size_t i = 0; i < strlen(string); i++)
	{
		char character = string[i];
		switch (character)
		{
			// Put element in stack list
			case '(':
			case '{':
			case '[':
			{
				push(stack, identifyBracket(character));
				break;
			}

			// Pull element in stack list
			case ')':
			case '}':
			case ']':
			{
				int prev = pop(stack);
				if (prev != identifyBracket(character))
				{
					deleteStack(&stack);
					return false;
				}
				break;
			}
		}
	}
	bool isCorrect = isEmpty(stack);
	deleteStack(&stack);
	return isCorrect;
}

bool test(void)
{
	bool isPassed = true;
	Stack* stack = createStack();

	push(stack, ROUND);
	push(stack, SQUARE);
	push(stack, CURLY);
	isPassed = isPassed && pop(stack) == CURLY;
	isPassed = isPassed && pop(stack) == SQUARE;
	isPassed = isPassed && pop(stack) == ROUND;
	isPassed = isPassed && isEmpty(stack);
	isPassed = isPassed && checkExpression("({})[]");
	isPassed = isPassed && !checkExpression("([)])");
	deleteStack(&stack);
	return isPassed;
}

int main()
{
	if (!test())
	{
		printf("Test Failed");
		return;
	}
	char* string = malloc(sizeof(char) * 100);
	if (string == NULL)
	{
		return;
	}

	printf(">> ");
	scanf("%[^\n]s", string);
	if (checkExpression(string))
	{
		printf("Correct\n");
	}
	else
	{
		printf("Wrong\n");
	}
	free(string);
}