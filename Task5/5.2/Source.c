#define _CRT_SECURE_NO_WARNINGS
#include "Stack.h"
#include <stdio.h>
#include <stdbool.h>

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
	return;
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

	// Create stack
	Stack* stack = createStack();
	printf(">> ");
	while (true)
	{
		// Scan character
		char character = ' ';
		scanf("%c", &character);
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
					printf("Wrong\n");
					deleteStack(&stack);
					return;
				}
				break;
			}

			// Print the result
			case '\n':
			{
				printf(isEmpty(stack) ? "Correct\n" : "Wrong\n");
				deleteStack(&stack);
				return;
			}
		}
	}
}