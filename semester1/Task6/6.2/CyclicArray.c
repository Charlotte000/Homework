#include "CyclicArray.h"
#include <stdlib.h>
#include <stdio.h>

CyclicArray* createArray(void)
{
	CyclicArray* newElement = malloc(sizeof(CyclicArray));
	if (newElement == NULL)
	{
		return NULL;
	}
	newElement->value = NULL;
	newElement->next = NULL;
	newElement->prev = NULL;
	return newElement;
}

void addElement(CyclicArray* head, int value)
{
	if (head->next == NULL)
	{
		head->value = value;
		head->next = head;
		head->prev = head;
		return;
	}
	CyclicArray* newElement = createArray();
	newElement->value = value;

	newElement->prev = head->prev;
	head->prev->next = newElement;

	newElement->next = head;
	head->prev = newElement;

}

void deleteElement(CyclicArray** head, int value)
{
	if ((*head)->value == value)
	{
		(*head)->next->prev = (*head)->prev;
		(*head)->prev->next = (*head)->next;
		CyclicArray* newHead = (*head)->next;
		free(*head);
		*head = newHead;
		return;
	}

	CyclicArray* cursor = (*head)->next;
	while (cursor != *head)
	{
		if (cursor->value == value)
		{
			cursor->next->prev = cursor->prev;
			cursor->prev->next = cursor->next;
			free(cursor);
			return;
		}
		cursor = cursor->next;
	}
}

void deleteArray(CyclicArray** head)
{
	CyclicArray* cursor = *head;
	while (cursor != *head)
	{
		cursor = cursor->prev;
		free(cursor->next);
	}
	free(*head);
	*head = NULL;
}

int getSize(CyclicArray* head)
{
	int size = 0;
	CyclicArray* first = head;
	CyclicArray* cursor = head;
	do
	{
		size++;
		cursor = cursor->next;
	} while (cursor != first);
	return size;
}

void printArray(CyclicArray* head)
{
	if (head->next == NULL)
	{
		return;
	}
	CyclicArray* first = head;
	CyclicArray* cursor = head;
	do
	{
		printf("%d ", cursor->value);
		cursor = cursor->next;
	} while (cursor != first);
	printf("\n");
}