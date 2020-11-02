#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void extendMassive(int** massive, int* massiveSize)
{
	*massiveSize += 50;
	int* newMassive = realloc(*massive, (*massiveSize) * sizeof(int));
	if (newMassive == NULL)
	{
		return;
	}
	free(*massive);
	*massive = newMassive;
}

void addValue(int* massive, int massiveIndex, int value)
{
	int first = 0, last = massiveIndex;

	// Check borders
	if (massive[first] > value)
	{
		first = -1;
		last = 0;
	}
	else if (massive[last] < value)
	{
		first = massiveIndex;
		last = massiveIndex + 1;
	}

	while (true)
	{
		if (last - first == 1)
		{
			// Insert value
			for (int i = massiveIndex; i >= last; i--)
			{
				massive[i + 1] = massive[i];
			}
			massive[last] = value;
			return;
		}

		// Divide by two pieces
		int middle = (first + last) / 2;
		if (massive[middle] > value)
		{
			last = middle;
		}
		else if (massive[middle] < value)
		{
			first = middle;
		}
		else
		{
			first = middle - 1;
			last = middle;
		}
	}
}

bool deleteValue(int* massive, int massiveIndex, int value)
{
	int first = 0, last = massiveIndex;

	// Check borders
	if (massive[first] > value || massive[last] < value)
	{
		return false;
	}

	while (true)
	{
		if (last - first == 1)
		{
			if (massive[first] == value)
			{
				last = first;
			}

			if (massive[last] == value)
			{
				// Delete value
				for (int i = last; i <= massiveIndex; i++)
				{
					massive[i] = massive[i + 1];
				}
				return true;
			}
			return false;
		}

		// Divide by two pieces
		int middle = (first + last) / 2;
		if (massive[middle] > value)
		{
			last = middle;
		}
		else if (massive[middle] < value)
		{
			first = middle;
		}
		else if (massive[middle] == value)
		{
			first = middle - 1;
			last = middle;
		}
	}
}

void printMassive(int* massive, int massiveIndex)
{
	for (int i = 0; i <= massiveIndex; i++)
	{
		printf("%d ", massive[i]);
	}
	printf("\n");
}

bool test(void)
{
	bool isPassed = true;

	int* massive = malloc(sizeof(int) * 5);
	if (massive == NULL)
	{
		return;
	}
	massive[0] = 1;
	massive[1] = 1;
	massive[2] = 5;
	massive[3] = 6;
	addValue(massive, 3, 2);
	isPassed = isPassed && massive[2] == 2;

	isPassed = isPassed && deleteValue(massive, 4, 1) && massive[1] == 2;

	isPassed = isPassed && !deleteValue(massive, 4, 456456);

	addValue(massive, 4, 45);
	isPassed = isPassed && massive[5] == 45;

	addValue(massive, 5, 0);
	isPassed = isPassed && massive[0] == 0;

	return isPassed;
}

int main()
{
	if (!test())
	{
		printf("Test failed!");
		return;
	}

	printf("0 - Exit\n");
	printf("1 - Add value\n");
	printf("2 - Delete value\n");
	printf("3 - Print values\n");

	int massiveSize = 50;
	int massiveIndex = -1;
	int* massive = malloc(sizeof(int) * massiveSize);
	if (massive == NULL)
	{
		return;
	}
	while (true)
	{
		char character = ' ';
		printf(">> ");
		scanf("%c", &character);
		switch (character)
		{
		case '0':
		{
			return;
		}
		case '1':
		{
			int value = 0;
			printf("Input value: ");
			scanf("%d", &value);
			if (massiveIndex + 1 >= massiveSize)
			{
				extendMassive(&massive, &massiveSize);
			}
			addValue(massive, massiveIndex, value);
			massiveIndex++;
			break;
		}
		case '2':
		{
			int value = 0;
			printf("Input value: ");
			scanf("%d", &value);
			if (deleteValue(massive, massiveIndex, value))
			{
				massiveIndex--;
			}
			break;
		}
		case '3':
		{
			printMassive(massive, massiveIndex);
			break;
		}

		}
	}
}