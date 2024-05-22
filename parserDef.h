// Group No. : 13
// Adarsh Goel 2020B3A70821P
// Chinmay Anand 2020B3A70800P
// Arjoo Kumari 2020B3A70770P
// Mehak Agarwal 2020B3A70868P
// Jay Prakash Mundhra 2020B3A70799P
#ifndef PARSER_DEF_H
#define PARSER_DEF_H

#include "grammar.h"
#include "tree.h"
#include "hashMap.h"
#include "stack.h"
#include "lexer.h"

struct non_terminal
{
    char* name;
    int nullable;
    int* first;
    int* follow;
    int first_size;
    int first_capacity;
    int follow_size;
    int follow_capacity;
    int rule_size;
    int rule_capacity;
    int is_computed_first;
    int is_computed_follow;
    RULE* associated_rules;
    RULE* parse_table;
};
typedef struct non_terminal* NON_TERMINAL;

struct non_terminal_list
{
    int size;
    int capacity;
    NON_TERMINAL* enteries;
};

typedef struct non_terminal_list* NON_TERMINAL_LIST;




#endif