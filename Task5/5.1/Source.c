#define _CRT_SECURE_NO_WARNINGS
#include "Stack.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

bool test(void)
{
	bool isPassed = true;
	Stack* stack = createStack();
	int value1 = 0;
	int value2 = 0;
	push(stack, 1);
	push(stack, 5);
	value2 = pop(stack);
	value1 = pop(stack);
	isPassed = isPassed && (value1 + value2 == 6);

	push(stack, 6);
	push(stack, 2);
	value2 = pop(stack);
	value1 = pop(stack);
	isPassed = isPassed && (value1 / value2 == 3);

	push(stack, 7);
	push(stack, 3);
	value2 = pop(stack);
	value1 = pop(stack);
	isPassed = isPassed && (value1 * value2 == 21);

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
		if (character == '\n')
		{
			break;
		}

		if (isdigit(character))
		{
			// Add digit to stack
			push(stack, atoi(&character));
		}
		else if (character != ' ')
		{
			// Get two previous items 
			if (isEmpty(stack))
			{
				break;
			}
			int value2 = pop(stack);
			if (isEmpty(stack))
			{
				break;
			}
			int value1 = pop(stack);

			// Do math
			switch (character)
			{
			case '+':
			{
				push(stack, value1 + value2);
				break;
			}
			case '-':
			{
				push(stack, value1 - value2);
				break;
			}
			case '*':
			{
				push(stack, value1 * value2);
				break;
			}
			case '/':
			{
				push(stack, value1 / value2);
				break;
			}
			}
		}
	}

	// Print the result
	if (isEmpty(stack))
	{
		printf("Error\n");
	}
	else
	{
		int result = pop(stack);
		if (isEmpty(stack))
		{
			printf("%d\n", result);
		}
		else
		{
			printf("Error\n");
		}
	}

	deleteStack(&stack);
}