#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct Warrior
{
	struct Warrior* next;
	int index;
} Warrior;

Warrior* createWarriors(int n)
{
	Warrior** warriors = malloc(sizeof(Warrior*) * n);
	if (warriors == NULL)
	{
		return NULL;
	}

	for (int i = 0; i < n; i++)
	{
		warriors[i] = malloc(sizeof(Warrior));
		if (warriors[i] == NULL)
		{
			return NULL;
		}
		warriors[i]->next = NULL;
		warriors[i]->index = i;
	}

	for (int i = 0; i < n; i++)
	{
		warriors[i]->next = warriors[(i + 1) % n];
	}
	return warriors[0];
}

void deleteWarrior(Warrior** head, int* n)
{
	Warrior* prev = *head;
	for (int i = 0; i < (*n) - 1; i++)
	{
		prev = prev->next;
	}
	prev->next = (*head)->next;
	free(*head);
	*head = prev->next;
	(*n)--;
	if (*n == 0)
	{
		*head = NULL;
	}
}

bool test(void)
{
	bool isPassed = true;

	int n = 3;
	Warrior* head = createWarriors(n);
	isPassed = isPassed && head->index == 0 && head->next->next->next->index == 0;

	deleteWarrior(&head, &n);
	isPassed = isPassed && head->index == 1 && head->next->next->index == 1;

	deleteWarrior(&head, &n);
	deleteWarrior(&head, &n);
	isPassed = isPassed && head == NULL;

	return isPassed;
}

int main()
{
	if (!test())
	{
		printf("Test failed!\n");
		return;
	}

	int n = 0;
	int m = 0;
	printf("Input n: ");
	scanf("%d", &n);
	printf("Input m: ");
	scanf("%d", &m);

	Warrior* head = createWarriors(n);

	int counter = 0;
	while (n > 1)
	{
		counter++;

		if (counter == m)
		{
			deleteWarrior(&head, &n);
			counter = 0;
		}
		else
		{
			head = head->next;
		}
	}

	printf("You should be %d in a row", head->index + 1);
}