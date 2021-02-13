#pragma once
#include <stdbool.h>

typedef struct Dictionary
{
	int key;
	char* value;
	struct Dictionary* left;
	struct Dictionary* right;
} Dictionary;

Dictionary* createDictionary(void);

void addValue(Dictionary** head, int key, char* value);

char* getValue(Dictionary* head, int key);

bool isExists(Dictionary* head, int key);

void deleteValue(Dictionary** head, int key);
