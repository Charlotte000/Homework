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

char* infix2postfix(char expression[100])
{
	Stack* stack = createStack();

	char postfix[100];
	for (int i = 0; i < (int) strlen(expression); i++)
	{
		char character = expression[i];
		if (character == ' ')
		{
			continue;
		}

		if (isdigit(character))
		{
			strcat(postfix, &character);
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
						strcat(postfix, &prevChar);
					}
					pop(stack);
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
			strcat(postfix, &currentChar);
		}
	}
	deleteStack(&stack);
	return postfix;
}

int main()
{
	char infix[100] = "( 2 + 3 ) / ( 3 * ( 1 + 1 ) )";
	infix2postfix(infix);
}