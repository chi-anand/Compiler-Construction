// Group No. : 13
// Adarsh Goel 2020B3A70821P
// Chinmay Anand 2020B3A70800P
// Arjoo Kumari 2020B3A70770P
// Mehak Agarwal 2020B3A70868P
// Jay Prakash Mundhra 2020B3A70799P
#include "stack.h"
#include "linked_list.h"
#include <stdlib.h>
#include "stdbool.h"
#define STACK_SIZE 1000

struct Stack
{
    LIST list;
};

Stack *newStack()
{
    Stack *s = (Stack *)malloc(sizeof(Stack));
    if(s != NULL)
        s -> list = createNewList();
    return s;
}
bool push(Stack *s, TREENODE element)
{
    if((s -> list) -> count == STACK_SIZE)
        return false;
    NODE new_node = createNewNode(element);
    if(new_node == NULL)
        return false;
    insertNodeIntoList(new_node, s -> list);
    return true;
}
TREENODE* top(Stack *s)
{
    if((s -> list) -> count == 0)
        return NULL;
    else
        return &(((s -> list) -> head) -> data);
}
bool pop(Stack *s)
{
    if((s -> list) -> count == 0)
        return false;
    removeFirstNode(s -> list);
    return true;
}
bool isEmpty(Stack *s)
{
    if((s -> list) -> count == 0)
        return true;
    else
        return false;
}
void freeStack(Stack *s)
{
    destroyList(s -> list);
    free(s);
}