#define _CRT_SECURE_NO_WARNINGS

#include "HashTable.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#define LoadFactor .7

HashTable* createTable(int (*hash)(char*, int))
{
	HashTable* newHash = malloc(sizeof(HashTable));
	if (newHash == NULL)
	{
		return NULL;
	}
	newHash->hashFunction = hash;
	newHash->maxSize = 10;
	newHash->table = calloc(newHash->maxSize, sizeof(Data*));
	if (newHash->table == NULL)
	{
		free(newHash);
		return NULL;
	}
	return newHash;
}

void extendHash(HashTable* hash)
{
	// Get filled hash count
	int count = 0;
	for (int i = 0; i < hash->maxSize; i++)
	{
		if (hash->table[i] != NULL)
		{
			count++;
		}
	}

	// Fill factor
	if ((float)count / hash->maxSize >= LoadFactor)
	{
		Data** oldTable = hash->table;
		int oldSize = hash->maxSize;

		hash->maxSize *= 2;
		Data** newTable = calloc(hash->maxSize, sizeof(Data*));
		if (newTable == NULL)
		{
			return;
		}
		for (int i = 0; i < oldSize; i++)
		{
			if (oldTable[i] != NULL)
			{
				newTable[hash->hashFunction(oldTable[i]->key, hash->maxSize)] = oldTable[i];
			}
		}
		hash->table = newTable;
		free(oldTable);
	}
}

void pushValue(HashTable* hash, char* key, int value)
{
	extendHash(hash);

	const int id = hash->hashFunction(key, hash->maxSize);

	// Change existing hash
	Data* cursor = hash->table[id];
	while (cursor != NULL)
	{
		if (strcmp(key, cursor->key) == 0)
		{
			cursor->value = value;
			return;
		}
		cursor = cursor->next;
	}

	// Create new hash
	Data* newData = malloc(sizeof(Data));
	if (newData == NULL)
	{
		return;
	}
	newData->key = malloc(sizeof(char) * 100);
	if (newData->key == NULL)
	{
		free(newData);
		return;
	}
	strcpy(newData->key, key);
	newData->value = value;
	newData->next = NULL;

	if (hash->table[id] == NULL)
	{
		hash->table[id] = newData;
		return;
	}
	
	// Append hash
	newData->next = hash->table[id];
	hash->table[id] = newData;
}

int popValue(HashTable* hash, char* key)
{
	const int id = hash->hashFunction(key, hash->maxSize);
	Data* cursor = hash->table[id];


	// Is empty hash
	if (cursor == NULL)
	{
		return NULL;
	}

	// Is head
	if (strcmp(key, cursor->key) == 0)
	{
		Data* oldData = cursor;
		int oldValue = cursor->value;
		hash->table[id] = cursor->next;
		free(oldData->key);
		free(oldData);
		return oldValue;
	}

	// Search hash
	while (cursor != NULL && cursor->next != NULL)
	{
		if (strcmp(key, cursor->next->key) == 0)
		{
			Data* oldData = cursor->next;
			int oldValue = cursor->next->value;
			cursor->next = cursor->next->next;
			free(oldData->key);
			free(oldData);
			return oldValue;
		}
		cursor = cursor->next;
	}
	return NULL;
}

bool isExists(HashTable* hash, char* key)
{
	int id = hash->hashFunction(key, hash->maxSize);

	// Search hash
	Data* cursor = hash->table[id];
	while (cursor != NULL)
	{
		if (strcmp(key, cursor->key) == 0)
		{
			return true;
		}
		cursor = cursor->next;
	}
	return false;
}

int getValue(HashTable* hash, char* key)
{
	const int id = hash->hashFunction(key, hash->maxSize);

	// Search hash
	Data* cursor = hash->table[id];
	while (cursor != NULL)
	{
		if (strcmp(key, cursor->key) == 0)
		{
			return cursor->value;
		}
		cursor = cursor->next;
	}
	return NULL;
}

void deleteHash(HashTable** hash)
{
	for (int i = 0; i < (*hash)->maxSize; i++)
	{
		Data* cursor = (*hash)->table[i];
		while (cursor != NULL)
		{
			Data* oldData = cursor;
			cursor = cursor->next;

			free(oldData->key);
			free(oldData);
		}
	}
	free((*hash)->table);
	free(*hash);
	*hash = NULL;
}