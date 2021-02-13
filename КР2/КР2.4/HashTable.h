#pragma once
#include <stdbool.h>

typedef struct HashTable HashTable;

// Creates new hash table
HashTable* createTable();

// Add value to hash table
void pushValue(HashTable* hash, char key, int value);

// Deletes value in the table, returns true if value was in the table
int popValue(HashTable* hash, char key);

// Returns true if value is in the table
bool isExists(HashTable* hash, char key);

// Deletes table
void deleteHash(HashTable** hash);

// Returns value by key
int getValue(HashTable* hash, char key);

