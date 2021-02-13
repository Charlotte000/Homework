#define _CRT_SECURE_NO_WARNINGS

#include "Stack.h"
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int getLevelOfOperator(char character)
{
	switch (character)
	{
	case '*':
	case '/':
	{
		return 1;
	}
	case '-':
	case '+':
	{
		return 2;
	}
	case '(':
	case ')':
	{
		return 3;
	}
	}
	return -1;
}

char* infix2postfix(char* expression)
{
	Stack* stack = createStack();

	char* postfix = malloc(sizeof(char) * 100);
	if (postfix == NULL)
	{
		return NULL;
	}
	int postfixIndex = 0;
	for (size_t i = 0; i < strlen(expression); i++)
	{
		char character = expression[i];
		if (character == ' ')
		{
			continue;
		}

		if (isdigit(character))
		{
			postfix[postfixIndex] = character;
			postfix[postfixIndex + 1] = ' ';
			postfixIndex += 2;
		}
		else if (character == '(')
		{
			push(stack, (int) character);
		}
		else if (getLevelOfOperator(character) > 0)
		{
			int level = getLevelOfOperator(character);
			while (!isEmpty(stack))
			{
				char prevChar = (char) pop(stack);
				int prevLevel = getLevelOfOperator(prevChar);
				if (prevLevel > 0 && prevLevel <= level)
				{
					if (prevChar != '(' && prevChar != ')')
					{
						postfix[postfixIndex] = prevChar;
						postfix[postfixIndex + 1] = ' ';
						postfixIndex += 2;
					}
				}
				else
				{
					push(stack, (int) prevChar);
					break;
				}
			}
			push(stack, (int) character);
		}
	}

	while (!isEmpty(stack))
	{
		char currentChar = (char) pop(stack);
		if (currentChar != '(' && currentChar != ')')
		{
			postfix[postfixIndex] = currentChar;
			postfix[postfixIndex + 1] = ' ';
			postfixIndex += 2;
		}
	}
	postfix[postfixIndex] = '\0';
	deleteStack(&stack);
	return postfix;
}

bool test(void)
{
	bool isPassed = true;

	char* answer = infix2postfix("1 + 2");
	isPassed = isPassed && strcmp(answer, "1 2 + ") == 0;
	free(answer);

	answer = infix2postfix("2 / (1+2)");
	isPassed = isPassed && strcmp(answer, "2 1 2 + / ") == 0;
	free(answer);

	answer = infix2postfix("(1 + 2 * (3 - 4)) / (5 * 6 / (7 + 8))");
	isPassed = isPassed && strcmp(answer, "1 2 3 4 - * + 5 6 * 7 8 + / / ") == 0;
	free(answer);
	return isPassed;
}

int main()
{
	if (!test())
	{
		printf("Test Failed");
		return;
	}

	char* infix = malloc(sizeof(char) * 100);
	if (infix == NULL)
	{
		return;
	}
	printf(">> ");
	scanf("%[^\n]s", infix);
	char* postfix = infix2postfix(infix);
	printf("%s", postfix);

	free(infix);
	free(postfix);
}