#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
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
	strcpy(phone.name, name);
	phone.number = malloc(sizeof(char) * (strlen(number) + 1));
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

int main()
{
	PhoneNumber phones[100];
	int phonesCount = loadPhoneNumber(phones);

	printf("0 - Exit\n1 - Create and save new phone\n2 - Get all phones\n3 - Find phone by name\n4 - Find phone by number\n");
	while (true)
	{
		int input;
		printf(">> ");
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
				for (int i = 0; i < phonesCount; i++)
				{
					if (!strcmp(phones[i].name, name))
					{
						printf("=========\nName: %s\nNumber: %s\n=========\n", phones[i].name, phones[i].number);
						break;
					}
				}
				break;
			}
			case 4:
			{
				char number[50];
				printf("Search by number: ");
				scanf("%s", number);
				for (int i = 0; i < phonesCount; i++)
				{
					if (!strcmp(phones[i].number, number))
					{
						printf("Name: %s\nNumber: %s\n=========\n", phones[i].name, phones[i].number);
						break;
					}
				}
				break;
			}
		}
	}
}