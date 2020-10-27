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

int main()
{
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
		{
			push(stack, ROUND);
			break;
		}
		case '{':
		{
			push(stack, CURLY);
			break;
		}
		case '[':
		{
			push(stack, SQUARE);
			break;
		}

		// Pull element in stack list
		case ')':
		{
			int prev = pop(stack);
			if (prev != ROUND)
			{
				printf("Wrong\n");
				deleteStack(&stack);
				return;
			}
			break;
		}
		case '}':
		{
			int prev = pop(stack);
			if (prev != CURLY)
			{
				printf("Wrong\n");
				deleteStack(&stack);
				return;
			}
			break;
		}
		case ']':
		{
			int prev = pop(stack);
			if (prev != SQUARE)
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