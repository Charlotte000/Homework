#define _CRT_SECURE_NO_WARNINGS

#include "SortedArray.h"
#include <stdio.h>
#include <stdbool.h>

bool test(void)
{
	bool isPassed = true;
	SortedArray* head = createArray();
	addElement(&head, 3);
	addElement(&head, 1);
	isPassed = isPassed && head->value == 1 && head->next->value == 3;
	deleteElement(&head, 1);
	isPassed = isPassed && head->value == 3 && head->next == NULL;
	deleteElement(&head, 123);
	isPassed = isPassed && head->value == 3 && head->next == NULL;
	deleteArray(&head);
	isPassed = isPassed && head == NULL;
	return isPassed;
}

int main()
{
	if (!test())
	{
		printf("Test Failed\n");
		return;
	}
	printf("0 - Exit\n");
	printf("1 - Add value\n");
	printf("2 - Delete value\n");
	printf("3 - Print values\n");

	SortedArray* head = createArray();
	while (true)
	{
		printf(">> ");
		char character = ' ';
		scanf("%c", &character);
		switch (character)
		{
			case '0':
			{
				deleteArray(&head);
				return;
			}
			case '1':
			{
				printf("Input value: ");
				int value = 0;
				scanf("%d", &value);

				addElement(&head, value);
				break;
			}
			case '2':
			{
				printf("Input value: ");
				int value = 0;
				scanf("%d", &value);

				deleteElement(&head, value);
				break;
			}
			case '3':
			{
				printElements(head);
				break;
			}
		}
	}
}