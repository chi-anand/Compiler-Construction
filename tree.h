// Group No. : 13
// Adarsh Goel 2020B3A70821P
// Chinmay Anand 2020B3A70800P
// Arjoo Kumari 2020B3A70770P
// Mehak Agarwal 2020B3A70868P
// Jay Prakash Mundhra 2020B3A70799P
#ifndef TREE_H
#define TREE_H

struct treeNode
{
    char* lexeme;
    int line_num;
    int token;
    struct treeNode* parent;
    int isLeaf;
    char* symbol;
    int size;
    int capacity;
    struct treeNode** children;
};

typedef struct treeNode* TREENODE;

#endif
