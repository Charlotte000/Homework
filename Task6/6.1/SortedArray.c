#include "SortedArray.h"
#include <stdlib.h>
#include <stdio.h>

SortedArray* createArray(void)
{
	SortedArray* newElement = malloc(sizeof(SortedArray));
	if (newElement == NULL)
	{
		return NULL;
	}
	newElement->next = NULL;
	newElement->value = NULL;
	return newElement;
}

void addElement(SortedArray** head, int value)
{
	if ((*head)->value == NULL)
	{
		(*head)->value = value;
		return;
	}
	SortedArray* newElement = createArray();
	newElement->value = value;
	SortedArray* cursor = *head;
	if (cursor->value > value)
	{
		*head = newElement;
		(*head)->next = cursor;
		return;
	}
	while (cursor->next != NULL)
	{
		if (cursor->value <= value && value <= cursor->next->value)
		{
			break;
		}
		cursor = cursor->next;
	}

	if (cursor->next)
	{
		newElement->next = cursor->next;
	}
	cursor->next = newElement;
}

void deleteElement(SortedArray** head, int value)
{
	if ((*head)->value == NULL)
	{
		return;
	}
	SortedArray* cursor = *head;
	if (cursor->value == value)
	{
		*head = cursor->next;
		free(cursor);
		if ((*head) == NULL)
		{
			*head = createArray();
		}
		return;
	}
	while (cursor->next != NULL)
	{
		if (cursor->next->value == value)
		{
			if (cursor->next->next != NULL)
			{
				SortedArray* newNext = cursor->next->next;
				free(cursor->next);
				cursor->next = newNext;
				return;
			}
			free(cursor->next);
			cursor->next = NULL;
			return;
		}
		cursor = cursor->next;
	}
}

void deleteArray(SortedArray** head)
{
	while ((*head)->value != NULL)
	{
		deleteElement(head, (*head)->value);
	}
	*head = NULL;
}

void printElements(SortedArray* head)
{
	if (head->value == NULL)
	{
		return;
	}
	SortedArray* cursor = head;
	while (cursor != NULL)
	{
		printf("%d ", cursor->value);
		cursor = cursor->next;
	}
	printf("\n");
}