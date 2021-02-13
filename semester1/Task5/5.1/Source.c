#define _CRT_SECURE_NO_WARNINGS
#include "Stack.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool calculate(char* string, int* result)
{
	Stack* stack = createStack();
	for (size_t i = 0; i < strlen(string); i++)
	{
		char character = string[i];
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

	if (isEmpty(stack))
	{
		deleteStack(&stack);
		return false;
	}
	else
	{
		int answer = pop(stack);
		if (isEmpty(stack))
		{
			*result = answer;
			deleteStack(&stack);
			return true;
		}
		else
		{
			deleteStack(&stack);
			return false;
		}
	}

}

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

	int answer = 0;
	isPassed = isPassed && calculate("1 5 +", &answer) && answer == 6;
	isPassed = isPassed && calculate("1 2 + 7 2 - *", &answer) && answer == 15;
	isPassed = isPassed && !calculate("1 + 5", &answer);

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

	int answer = 0;
	char* string = malloc(sizeof(char) * 100);
	if (string == NULL)
	{
		return;
	}
	printf(">> ");
	scanf("%[^\n]s", string);
	if (calculate(string, &answer))
	{
		printf("%d ", answer);
	}
	else
	{
		printf("Error");
	}
	free(string);
}