#pragma once

typedef struct CyclicArray
{
	int value;
	struct CyclicArray* next;
	struct CyclicArray* prev;
} CyclicArray;

CyclicArray* createArray(void);

void addElement(CyclicArray* head, int value);

void printArray(CyclicArray* head);

void deleteElement(CyclicArray** head, int value);

void deleteArray(CyclicArray** head);

int getSize(CyclicArray* head);
