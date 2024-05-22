// Group No. : 13
// Adarsh Goel 2020B3A70821P
// Chinmay Anand 2020B3A70800P
// Arjoo Kumari 2020B3A70770P
// Mehak Agarwal 2020B3A70868P
// Jay Prakash Mundhra 2020B3A70799P
#ifndef LEXER_H
#define LEXER_H

#include "lexerDef.h"


// define all the function.
LEX_OUT initialise_lexer_output();
void insert_lexeme_out(LEX_OUT lexer_output, char* lexeme, int token, int line_num);
void destroy_lex_out(LEX_OUT lexer_output);
void display_lexer_output(LEX_OUT lexer_output, char** token_to_string);
char *increment_pointer(int *fwd_pointer, char *buf1, char *buf2, char *fwd_buf, int* char_read, FILE* prog_fp, int *refill_flag);
char *decrement_pointer(int *fwd_pointer, char *buf1, char *buf2, char *fwd_buf, int *refill_flag);
char *get_lexeme(int* fwd_pointer, int* beg_pointer, char* fwd_buf, char* beg_buf);
LEX_OUT compute_tokens(char** token_to_string, int print_flag, FILE* prog_fp);


#endif