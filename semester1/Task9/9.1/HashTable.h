#pragma once
#include <stdbool.h>

typedef struct Data
{
	char* key;
	int value;
	struct Data* next;
} Data;

typedef struct HashTable
{
	Data** table;
	int maxSize;
	int (*hashFunction)(char*, int);
} HashTable;

HashTable* createTable(int (*hash)(char*, int));

void pushValue(HashTable* hash, char* key, int value);

int popValue(HashTable* hash, char* key);

bool isExists(HashTable* hash, char* key);

int getValue(HashTable* hash, char* key);

void deleteHash(HashTable** hash);
