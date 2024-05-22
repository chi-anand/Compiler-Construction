// Group No. : 13
// Adarsh Goel 2020B3A70821P
// Chinmay Anand 2020B3A70800P
// Arjoo Kumari 2020B3A70770P
// Mehak Agarwal 2020B3A70868P
// Jay Prakash Mundhra 2020B3A70799P
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "tree.h"

struct node
{
    TREENODE data;
    struct node *next;
};
typedef struct node node;
typedef node * NODE;

struct linked_list
{
    int count;
    NODE head;

};

typedef struct linked_list linked_list;
typedef linked_list * LIST;

LIST createNewList();
// This function allocates memory for a new list and returns a pointer to it.
// The list is empty and the count is set to 0.

NODE createNewNode(TREENODE data);
// This function allocates memory for a new node and returns a pointer to it.
// The next pointer is set to NULL and the data is set to the value passed in.

void insertNodeIntoList(NODE node, LIST list);
// This function inserts a node at the beginning of the list.

void removeFirstNode(LIST list);
// This function removes the first node from the list.

// void insertNodeAtEnd(NODE node, LIST list); // Not required for stack. Required for Queue
// This function inserts a node at the end of the list.

void destroyList(LIST list);
#endif