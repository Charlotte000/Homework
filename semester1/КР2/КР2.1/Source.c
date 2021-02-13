#define _CRT_SECURE_NO_WARNINGS

#include "LinkedList.h"
#include <stdio.h>
#include <stdbool.h>

LinkedList* readFile(char* fileName)
{
	LinkedList* list = createList();
	FILE* file = fopen(fileName, "r");
	while (!feof(file))
	{
		int number = 0;
		fscanf(file, "%d", &number);
		push(list, number);
	}
	fclose(file);
	return list;
}

bool test(void)
{
	bool isPassed = true;
	LinkedList* list = createList();

	LinkedList* invertedList = invert(list);
	isPassed = isPassed && isEmpty(invertedList);
	deleteList(&invertedList);

	push(list, 1);
	
	invertedList = invert(list);
	isPassed = isPassed && get(invertedList, 0) == 1;
	deleteList(&invertedList);

	push(list, 2);

	invertedList = invert(list);
	isPassed = isPassed && get(invertedList, 0) == 2 && get(invertedList, 1) == 1;
	deleteList(&invertedList);

	push(list, 3);

	invertedList = invert(list);
	isPassed = isPassed && get(invertedList, 0) == 3 && get(invertedList, 1) == 2 && get(invertedList, 2) == 1;
	deleteList(&invertedList);

	deleteList(&list);
	return isPassed;
}

int main()
{
	if (!test())
	{
		printf("Test Failed!\n");
		return;
	}

	LinkedList* list = readFile("data.txt");
	LinkedList* invertedList = invert(list);

	printList(list);
	printList(invertedList);

	deleteList(&list);
	deleteList(&invertedList);
}