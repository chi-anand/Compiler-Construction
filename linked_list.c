// Group No. : 13
// Adarsh Goel 2020B3A70821P
// Chinmay Anand 2020B3A70800P
// Arjoo Kumari 2020B3A70770P
// Mehak Agarwal 2020B3A70868P
// Jay Prakash Mundhra 2020B3A70799P
#include <stdbool.h>
#include <stdlib.h>
#include "linked_list.h"

LIST createNewList()
{
    LIST new_list = malloc(sizeof(linked_list));
    new_list -> count = 0;
    new_list -> head = NULL;
    return new_list;
}
NODE createNewNode(TREENODE data)
{
    NODE new_node = malloc(sizeof(node));
    new_node -> data = data;
    new_node -> next = NULL;
    return new_node;
}
void insertNodeIntoList(NODE node, LIST list)
{
    node -> next = list -> head;
    list -> head = node;
    (list -> count)++; 
}
void removeFirstNode(LIST list)
{
    if(list -> count !=0)
    {
        NODE temp = list -> head;
        list -> head = temp -> next;
        (list -> count)--;
        free(temp); 
    }
}
void destroyList(LIST list)
{
    NODE temp = list -> head;
    while(temp != NULL)
    {
        NODE todelete =  temp;
        temp = temp -> next;
        free(todelete);
    }
    free(list);
}