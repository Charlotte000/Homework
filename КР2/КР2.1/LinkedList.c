#include "LinkedList.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct ListElement
{
	int value;
	struct ListElement* next;
} ListElement;

typedef struct LinkedList
{
	int length;
	ListElement* head;
} LinkedList;

bool isEmpty(LinkedList* list)
{
	return list->length == 0;
}

void push(LinkedList* list, int value)
{
	ListElement* newElement = malloc(sizeof(ListElement));
	if (newElement == NULL)
	{
		return;
	}
	newElement->value = value;
	newElement->next = NULL;

	if (isEmpty(list))
	{
		list->head = newElement;
	}
	else
	{
		ListElement* cursor = list->head;
		for (int i = 0; i < list->length - 1; i++)
		{
			cursor = cursor->next;
		}
		cursor->next = newElement;
	}
	list->length++;
}

int pop(LinkedList* list)
{
	if (isEmpty(list))
	{
		return 0;
	}

	ListElement** cursor = &(list->head);
	for (int i = 0; i < list->length - 1; i++)
	{
		cursor = &((*cursor)->next);
	}
	int value = (*cursor)->value;
	free(*cursor);
	*cursor = NULL;
	list->length--;
	return value;
}

void deleteList(LinkedList** list)
{
	while (!isEmpty(*list))
	{
		pop(*list);
	}
	free(*list);
	*list = NULL;
}

LinkedList* createList(void)
{
	LinkedList* list = malloc(sizeof(LinkedList));
	if (list == NULL)
	{
		return NULL;
	}
	list->head = NULL;
	list->length = 0;
	return list;
}

int get(LinkedList* list, int index)
{
	if (isEmpty(list))
	{
		return NULL;
	}
	ListElement* cursor = list->head;
	for (int i = 0; i < index; i++)
	{
		cursor = cursor->next;
		if (cursor == NULL)
		{
			return NULL;
		}
	}
	return cursor->value;
}

LinkedList* invert(LinkedList* list)
{
	LinkedList* newList = createList();
	ListElement* cursor = list->head;
	for (int i = 0; i < list->length; i++)
	{
		ListElement* newElement = malloc(sizeof(ListElement));
		if (newElement == NULL)
		{
			return;
		}
		newElement->value = cursor->value;
		cursor = cursor->next;
		ListElement* oldHead = newList->head;
		newList->head = newElement;
		newList->head->next = oldHead;
	}
	newList->length = list->length;
	return newList;
}

void printList(LinkedList* list)
{
	if (isEmpty(list))
	{
		return;
	}
	ListElement* cursor = list->head;
	while (cursor != NULL)
	{
		printf("%d ", cursor->value);
		cursor = cursor->next;
	}
	printf("\n");
}