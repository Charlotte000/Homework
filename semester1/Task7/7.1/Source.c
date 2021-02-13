#define _CRT_SECURE_NO_WARNINGS

#include "Dictionary.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void testClean(Dictionary* head)
{
	if (head->left)
	{
		testClean(head->left);
	}
	if (head->right)
	{
		testClean(head->right);
	}
	free(head);
}

bool test(void)
{
	bool isPassed = true;
	Dictionary* head = createDictionary();
	addValue(&head, 5, "hello");
	isPassed = isPassed && strcmp(getValue(head, 5), "hello") == 0;
	isPassed = isPassed && getValue(head, 123) == NULL;
	isPassed = isPassed && isExists(head, 5);
	isPassed = isPassed && !isExists(head, 123);
	addValue(&head, 1, "hi");
	isPassed = isPassed && strcmp(getValue(head, 1), "hi") == 0;
	isPassed = isPassed && isExists(head, 1);
	testClean(head);
	return isPassed;
}

int main()
{
	if (!test())
	{
		printf("Test Failed!\n");
		return;
	}

	Dictionary* head = createDictionary();

	printf("0 - exit\n");
	printf("1 - add value\n");
	printf("2 - get value by key\n");
	printf("3 - is value exists\n");
	printf("4 - delete value\n");

	while (true)
	{
		printf(">> ");
		char character = ' ';
		scanf("%c", &character);
		switch (character)
		{
			case '0':
			{
				while (head != NULL)
				{
					deleteValue(&head, head->key);
				}
				return;
			}
			case '1':
			{
				int key = 0;
				char *value = malloc(sizeof(char) * 100);
				if (value == NULL)
				{
					return NULL;
				}
				printf("Input key: ");
				scanf("%d", &key);
				printf("Input value: ");
				scanf("%s", value);
				addValue(&head, key, value);
				break;
			}
			case '2':
			{
				int key = 0;
				printf("Input key: ");
				scanf("%d", &key);
				printf("%s\n", getValue(head, key));
				break;
			}
			case '3':
			{
				int key = 0;
				printf("Input key: ");
				scanf("%d", &key);
				printf(isExists(head, key) ? "Found\n" : "Not Found\n");
				break;
			}
			case '4':
			{
				int key = 0;
				printf("Input key: ");
				scanf("%d", &key);
				deleteValue(&head, key);
				break;
			}
		}
	}
}