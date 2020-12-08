#define _CRT_SECURE_NO_WARNINGS

#include "Stack.h"
#include <stdio.h>
#include <stdbool.h>

void readFile(char* fileName, Stack* stack, int* a, int* b)
{
	FILE* file = fopen(fileName, "r");

	fscanf(file, "%d %d", a, b);

	while (!feof(file))
	{
		int value = 0;
		fscanf(file, "%d", &value);
		push(stack, value);

	}
	fclose(file);
}


void process(Stack* stack, int a, int b, Stack* lessThan, Stack* inInterval, Stack* moreThan)
{
	while (!isEmpty(stack))
	{
		int value = pop(stack);
		if (value < a)
		{
			push(lessThan, value);
		}
		else if (value > b)
		{
			push(moreThan, value);
		}
		else
		{
			push(inInterval, value);
		}
	}
}

void printValues(Stack* stack)
{
	while (!isEmpty(stack))
	{
		printf("%d ", pop(stack));
	}
}

bool test(void)
{
	bool isPassed = true;
	Stack* stack = createStack();
	Stack* lessThan = createStack();
	Stack* inInterval = createStack();
	Stack* moreThan = createStack();

	process(stack, 1, 5, lessThan, inInterval, moreThan);
	isPassed = isPassed && isEmpty(lessThan) && isEmpty(inInterval) && isEmpty(moreThan);

	push(stack, 5);
	process(stack, 1, 5, lessThan, inInterval, moreThan);
	isPassed = isPassed && isEmpty(lessThan) && !isEmpty(inInterval) && isEmpty(moreThan);
	
	pop(inInterval);

	push(stack, 2);
	push(stack, 3);
	process(stack, 1, 5, lessThan, inInterval, moreThan);
	isPassed = isPassed && isEmpty(lessThan) && isEmpty(moreThan) && pop(inInterval) == 2 && pop(inInterval) == 3;

	deleteStack(&stack);
	deleteStack(&lessThan);
	deleteStack(&inInterval);
	deleteStack(&moreThan);
	return isPassed;
}

int main()
{
	if (!test())
	{
		printf("Test Failed!\n");
		return;
	}

	Stack* stack = createStack();
	int a = 0;
	int b = 0;
	readFile("data.txt", stack, &a, &b);

	Stack* lessThan = createStack();
	Stack* inInterval = createStack();
	Stack* moreThan = createStack();

	process(stack, a, b, lessThan, inInterval, moreThan);

	printf("Less than a: ");
	printValues(lessThan);
	printf("\n");

	printf("In interval between a and b: ");
	printValues(inInterval);
	printf("\n");

	printf("More than b: ");
	printValues(moreThan);
	printf("\n");

	deleteStack(&stack);
	deleteStack(&lessThan);
	deleteStack(&inInterval);
	deleteStack(&moreThan);
}