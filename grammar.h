// Group No. : 13
// Adarsh Goel 2020B3A70821P
// Chinmay Anand 2020B3A70800P
// Arjoo Kumari 2020B3A70770P
// Mehak Agarwal 2020B3A70868P
// Jay Prakash Mundhra 2020B3A70799P
#ifndef GRAMMAR_H
#define GRAMMAR_H


struct rule_unit
{
    char* production_rule_unit;
    struct rule_unit* next;
};

typedef struct rule_unit* RULE;


// define grammar struct
struct grammar
{
    int size;
    int capacity;
    RULE* rules;
};
typedef struct grammar* GRAMMAR;




#endif