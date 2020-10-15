#include <stdlib.h>
#include <stdbool.h>

typedef struct Stack
{
	int value;
	struct Stack* next;
} Stack;

bool isEmpty(Stack** head)
{
	return *head == NULL;
}

Stack* createStack(int value)
{
	Stack* newItem = malloc(sizeof(Stack));
	if (newItem == NULL)
	{
		return NULL;
	}
	newItem->value = value;
	newItem->next = NULL;
	return newItem;
}

void push(Stack** head, int value)
{
	Stack* newItem = createStack(value);
	newItem->next = *head;
	*head = newItem;
}

int pop(Stack** head)
{
	if (isEmpty(head))
	{
		return -1;
	}
	int value = (*head)->value;
	Stack* oldHead = *head;
	*head = (*head)->next;
	free(oldHead);
	return value;
}

void deleteStack(Stack** head)
{
	while (!isEmpty(head))
	{
		pop(head);
	}
}
