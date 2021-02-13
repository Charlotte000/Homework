#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Boyer–Moore string-search algorithm
int search(const char* string, const char* substring)
{
	const int lengthString = strlen(string);
	const int lengthSub = strlen(substring);

	int stopSymbols[255] = { 0 };
	for (int i = 0; i < 255; i++)
	{
		stopSymbols[i] = lengthSub;
	}

	for (int i = lengthSub - 2; i >= 0; i--)
	{
		if (stopSymbols[substring[i]] == lengthSub)
		{
			stopSymbols[substring[i]] = lengthSub - i - 1;
		}
	}

	int cursor = lengthSub - 1;
	while (cursor < lengthString)
	{
		bool isFound = true;
		for (int i = 0; i < lengthSub; i++)
		{
			if (string[cursor - i] != substring[lengthSub - 1 - i])
			{
				cursor += stopSymbols[string[cursor]];
				isFound = false;
				break;
			}
		}
		if (isFound)
		{
			return cursor - lengthSub + 1;
		}
	}
	return -1;
}

char* readFile(char* fileName)
{
	char* input = calloc(100, sizeof(char));
	if (input == NULL)
	{
		return NULL;
	}
	FILE* file = fopen(fileName, "rb");
	fread(input, sizeof(char), 100, file);
	fclose(file);
	return input;
}

bool test(void)
{
	bool isPassed = true;
	isPassed = isPassed && search("abcdef", "g") == -1;
	isPassed = isPassed && search("g", "abcdef") == -1;
	isPassed = isPassed && search("", "abcdef") == -1;
	isPassed = isPassed && search("abcdef", "") == 0;
	isPassed = isPassed && search("abababbba", "bba") == 6;
	return isPassed;
}

int main()
{
	if (!test())
	{
		printf("Test Failed!\n");
		return;
	}

	char* substring = calloc(100, sizeof(char));
	if (substring == NULL)
	{
		return;
	}
	char* string = readFile("data.txt");
	printf("String:    %s\n", string);
	printf("Substring: ");
	scanf("%s", substring);

	printf("%d ", search(string, substring));

	free(string);
	free(substring);
}