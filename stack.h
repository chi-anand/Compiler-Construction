// Group No. : 13
// Adarsh Goel 2020B3A70821P
// Chinmay Anand 2020B3A70800P
// Arjoo Kumari 2020B3A70770P
// Mehak Agarwal 2020B3A70868P
// Jay Prakash Mundhra 2020B3A70799P
#ifndef STACK_H
#define STACK_H

#include "stdbool.h"
#include "tree.h"

typedef struct Stack Stack; // Stack is a pointer to a struct stack

Stack *newStack(); 
// Returns a pointer to a new stack. Returns NULL if memory allocation fails

bool push(Stack *stack, TREENODE element); 
// Pushes element onto stack. Returns false if memory allocation fails

TREENODE* top(Stack *stack); 
// Returns a pointer to the top element. Returns NULL if stack is empty

bool pop(Stack *stack); 
// Pops the top element and returns true. Returns false if stack is empty

bool isEmpty(Stack *stack);
// Returns true if stack is empty. Returns false otherwise

void freeStack(Stack *stack); 
// Frees all memory associated with stack

#endif