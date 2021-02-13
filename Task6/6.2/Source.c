#define _CRT_SECURE_NO_WARNINGS

#include "CyclicArray.h"
#include <stdio.h>
#include <stdbool.h>

CyclicArray* createWarriors(int n)
{
	CyclicArray* head = createArray();
	for (int i = 0; i < n; i++)
	{
		addElement(head, i);
	}
	return head;
}

int getNumber(int n, int m)
{
	CyclicArray* head = createWarriors(n);
	CyclicArray* cursor = head;
	int counter = 0;
	while (getSize(head) > 1)
	{
		counter++;
		cursor = cursor->next;

		if (counter == m)
		{
			deleteElement(&head, cursor->prev->value);
			counter = 0;
		}
	}
	int result = cursor->value;
	deleteArray(&head);
	return result + 1;
}

bool test(void)
{
	bool isPassed = true;
	CyclicArray* head = createArray();
	addElement(head, 1);
	addElement(head, 2);
	addElement(head, 3);
	isPassed = isPassed && head->value == 1 && head->next->value == 2 && head->next->next->value == 3 && head->next->next->next->value == 1;
	deleteElement(&head, 1);
	isPassed = isPassed && head->value == 2 && head->next->value == 3 && head->next->next->value == 2;
	deleteArray(&head);
	isPassed = isPassed && head == NULL;
	isPassed = isPassed && getNumber(3, 2) == 3;
	isPassed = isPassed && getNumber(5, 3) == 4;
	isPassed = isPassed && getNumber(20, 7) == 3;
	return isPassed;
}

int main()
{
	if (!test())
	{
		printf("Test Failed\n");
		return;
	}
	int n = 0;
	int m = 0;
	printf("Input n: ");
	scanf("%d", &n);
	printf("Input m: ");
	scanf("%d", &m);
	printf("%d", getNumber(n, m));
}