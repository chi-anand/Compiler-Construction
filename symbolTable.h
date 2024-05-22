// Group No. : 13
// Adarsh Goel 2020B3A70821P
// Chinmay Anand 2020B3A70800P
// Arjoo Kumari 2020B3A70770P
// Mehak Agarwal 2020B3A70868P
// Jay Prakash Mundhra 2020B3A70799P
#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include "hashMap.h"
// define the structure for symbol table row
struct sym_table_row
{
    char *lexeme;
    int token;
};
typedef struct sym_table_row* SYM_ROW;

// define structure for symbol table
struct sym_table
{
    int size;
    int capacity;
    SYM_ROW *enteries;
};
typedef struct sym_table* SYM_TABLE;

// define all the function.
SYM_TABLE populate_symbol_table();
SYM_ROW lookup_symbol_table(SYM_TABLE symbol_table, char* lexeme);
void insert_lexeme_token(SYM_TABLE symbol_table, char* lexeme, int token);
void destroy_symbol_table(SYM_TABLE symbol_table);
void display_symbol_table(SYM_TABLE symbol_table, char** token_to_string);

#endif