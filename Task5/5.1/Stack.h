#include <stdbool.h>

typedef Stack;

bool isEmpty(Stack**); // Check if stack item is NULL

Stack* createStack(int); // Init new stack item

void push(Stack**, int); // Add new stack's head

int pop(Stack**); // Delete stack's head returning it's value or -1 if head is empty

void deleteStack(Stack**); // Delete whole chain of stack elements
