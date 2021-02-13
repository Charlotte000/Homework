#pragma once
#include <stdbool.h>

typedef Stack;

// Add new stack's head
void push(Stack* stack, int value);

// Delete stack's head returning it's value or -1 if head is empty
int pop(Stack* stack);

// Check if stack doesn't have elements
bool isEmpty(Stack* stack);

// Delete stack
void deleteStack(Stack** stack);

// Init new stack
Stack* createStack(void);