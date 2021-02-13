#pragma once
typedef struct SortedArray
{
	struct SortedArray* next;
	int value;
} SortedArray;

SortedArray* createArray(void);

void addElement(SortedArray** head, int value);

void printElements(SortedArray* head);

void deleteElement(SortedArray** head, int value);

void deleteArray(SortedArray** head);