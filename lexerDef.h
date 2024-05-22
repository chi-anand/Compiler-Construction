// Group No. : 13
// Adarsh Goel 2020B3A70821P
// Chinmay Anand 2020B3A70800P
// Arjoo Kumari 2020B3A70770P
// Mehak Agarwal 2020B3A70868P
// Jay Prakash Mundhra 2020B3A70799P
#ifndef LEXER_DEF_H
#define LEXER_DEF_H

#include"symbolTable.h"

// define the structure for lexer output row
struct lex_out_row
{
    char *lexeme;
    int token;
    int line_num;
};
typedef struct lex_out_row* LEX_ROW;

// define structure for lex output
struct lex_out
{
    int size;
    int capacity;
    LEX_ROW *enteries;
};
typedef struct lex_out* LEX_OUT;



#endif