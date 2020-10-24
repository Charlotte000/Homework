#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct
{
	char *name;
	char *number;
} PhoneNumber;

PhoneNumber createPhoneNumber(char *name, char *number)
{
	PhoneNumber phone;
	phone.name = malloc(sizeof(char) * (strlen(name) + 1));
	if (phone.name == NULL)
	{
		return;
	}
	strcpy(phone.name, name);
	phone.number = malloc(sizeof(char) * (strlen(number) + 1));
	if (phone.number == NULL)
	{
		return;
	}
	strcpy(phone.number, number);
	return phone;
}

void savePhoneNumber(PhoneNumber phone, int phonesCount)
{
	FILE* file = fopen("data.txt", "a");
	if (file == NULL)
	{
		return -1;
	}

	if (phonesCount > 0)
	{
		fputs("\n", file);
	}
	fputs(phone.name, file);
	fputs("\n", file);
	fputs(phone.number, file);
	fclose(file);
}

int loadPhoneNumber(PhoneNumber phones[100])
{
	FILE* file = fopen("data.txt", "r");
	if (file == NULL)
	{
		return 0;
	}

	int phoneCount = 0;
	while (!feof(file))
	{
		char name[50];
		char number[50];
		fscanf(file, "%s", name);
		fscanf(file, "%s", number);
		phones[phoneCount] = createPhoneNumber(name, number);
		phoneCount++;
	}
	fclose(file);
	return phoneCount;
}

int searchByName(PhoneNumber phones[100], int phonesCount, char name[50])
{
	for (int i = 0; i < phonesCount; i++)
	{
		if (strcmp(phones[i].name, name) == 0)
		{
			return i;
		}
	}
	return -1;
}

int searchByNumber(PhoneNumber phones[100], int phonesCount, char number[50])
{
	for (int i = 0; i < phonesCount; i++)
	{
		if (strcmp(phones[i].number, number) == 0)
		{
			return i;
		}
	}
	return -1;
}

bool test(void)
{
	bool isPassed = true;
	PhoneNumber phones[2];
	PhoneNumber phone1 = { "Ivan", "123" };
	PhoneNumber phone2 = { "Vladimir", "4785" };
	phones[0] = phone1;
	phones[1] = phone2;
	
	if (searchByName(phones, 2, "Vladimir") != 1)
	{
		isPassed = false;
	}
	if (searchByName(phones, 2, "BlaBlaBla") != -1)
	{
		isPassed = false;
	}

	if (searchByNumber(phones, 2, "123") != 0)
	{
		isPassed = false;
	}
	if (searchByNumber(phones, 2, "BlaBlaBla") != -1)
	{
		isPassed = false;
	}
	return isPassed;
}

int main()
{
	if (test() != true)
	{
		printf("Test failed!\n");
		return;
	}
	PhoneNumber phones[100];
	int phonesCount = loadPhoneNumber(phones);

	printf("0 - Exit\n");
	printf("1 - Create and save new phone\n");
	printf("2 - Get all phones\n");
	printf("3 - Find phone by name\n");
	printf("4 - Find phone by number\n");
	while (true)
	{
		printf(">> ");
		int input;
		scanf("%d", &input);
		
		switch (input)
		{
			case 0: return;
			case 1:
			{
				if (phonesCount == 99)
				{
					printf("Phone count limit!\n");
					break;
				}
				char name[50];
				printf("Name: ");
				scanf("%s", name);

				char number[50];
				printf("Number: ");
				scanf("%s", number);

				PhoneNumber phone = createPhoneNumber(name, number);
				phones[phonesCount] = phone;
				phonesCount++;

				savePhoneNumber(phone, phonesCount);
				printf("Saved\n");
				break;
			}
			case 2:
			{
				for (int i = 0; i < phonesCount; i++)
				{
					printf("Name: %s\nNumber: %s\n=========\n", phones[i].name, phones[i].number);
				}
				break;
			}
			
			case 3:
			{
				char name[50];
				printf("Search by name: ");
				scanf("%s", name);
				int index = searchByName(phones, phonesCount, name);
				if (index != -1)
				{
					printf("=========\n");
					printf("Name: %s\n", phones[index].name);
					printf("Number: %s\n", phones[index].number);
					printf("=========\n");
				}
				break;
			}
			case 4:
			{
				char number[50];
				printf("Search by number: ");
				scanf("%s", number);
				int index = searchByNumber(phones, phonesCount, number);
				if (index != -1)
				{
					printf("=========\n");
					printf("Name: %s\n", phones[index].name);
					printf("Number: %s\n", phones[index].number);
					printf("=========\n");
				}
				break;
			}
		}
	}
}