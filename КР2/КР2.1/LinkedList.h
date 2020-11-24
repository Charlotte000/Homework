#pragma once
#include <stdbool.h>

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

bool isEmpty(LinkedList* list);

void push(LinkedList* list, int value);

int pop(LinkedList* list);

void deleteList(LinkedList** list);

LinkedList* createList(void);

int get(LinkedList* list, int index);

LinkedList* invert(LinkedList* list);

void printList(LinkedList* list);