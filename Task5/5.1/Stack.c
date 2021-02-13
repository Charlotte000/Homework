#include "Stack.h"
#include <stdbool.h>
#include <stdlib.h>

typedef struct StackElement
{
	int value;
	struct StackElement* next;
} StackElement;


bool isEmpty(Stack* stack)
{
	return stack->head == NULL;
}

void push(Stack* stack, int value)
{
	StackElement* newElement = malloc(sizeof(StackElement));
	if (newElement == NULL)
	{
		return;
	}
	newElement->value = value;
	newElement->next = stack->head;
	stack->head = newElement;
}

int pop(Stack* stack)
{
	if (isEmpty(stack))
	{
		return -1;
	}
	int value = stack->head->value;
	StackElement* oldHead = stack->head;
	stack->head = stack->head->next;
	free(oldHead);
	return value;
}

void deleteStack(Stack** stack)
{
	while (!isEmpty(*stack))
	{
		pop(*stack);
	}
	free(*stack);
	*stack = NULL;
}

Stack* createStack(void)
{
	Stack* stack = malloc(sizeof(Stack));
	if (stack == NULL)
	{
		return NULL;
	}
	stack->head = NULL;
	return stack;
}