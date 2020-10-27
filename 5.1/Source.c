#define _CRT_SECURE_NO_WARNINGS
#include "Stack.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

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