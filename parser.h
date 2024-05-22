// Group No. : 13
// Adarsh Goel 2020B3A70821P
// Chinmay Anand 2020B3A70800P
// Arjoo Kumari 2020B3A70770P
// Mehak Agarwal 2020B3A70868P
// Jay Prakash Mundhra 2020B3A70799P
#ifndef PARSER_H
#define PARSER_H

#include "parserDef.h"

// define functions for grammar
GRAMMAR initialise_grammar();
RULE insert_production_rule_unit(RULE rule, char* production_rule_unit);
RULE get_rule(char* line);
void preprocess_grammar();
void insert_rule(GRAMMAR grammar, RULE rule);
void destroy_grammar();
void display_grammar();

// Functions for non terminal preprocessing
void insert_non_terminal(NON_TERMINAL_LIST non_terminal_list, char* non_terminal);
void insert_associated_rules(RULE rule, NON_TERMINAL_LIST non_terminal_list, int index);
void preprocess_non_terminal_list(GRAMMAR grammar, NON_TERMINAL_LIST non_terminal_list);
void display_non_terminal_list(NON_TERMINAL_LIST non_terminal_list);
void destroy_non_terminal_list(NON_TERMINAL_LIST non_terminal_list);
NON_TERMINAL_LIST initialise_non_terminal_list();

// Functions for computing first
int is_terminal(char* production_rule_unit);
void insert_first(NON_TERMINAL non_terminal, int terminal);
void append_first(NON_TERMINAL non_terminal_dest, NON_TERMINAL non_terminal_src);
void compute_first(NON_TERMINAL_LIST non_terminal_list, NON_TERMINAL non_terminal);
void compute_first_non_terminal(NON_TERMINAL_LIST non_terminal_list);
void display_first(NON_TERMINAL_LIST non_terminal_list);

// Functions for computing follow
int is_nullable_beta(NON_TERMINAL_LIST non_terminal_list, RULE beta);
int* compute_first_beta(NON_TERMINAL_LIST non_terminal_list, RULE beta);
void insert_follow(NON_TERMINAL non_terminal, int terminal);
void append_follow(NON_TERMINAL non_terminal, int* first_beta);
void compute_follow(NON_TERMINAL_LIST non_terminal_list, NON_TERMINAL non_terminal, int** marked);
int  copy_follow(NON_TERMINAL non_terminal_dest, NON_TERMINAL non_terminal_src);
void final_follow(NON_TERMINAL_LIST non_terminal_list, int** marked);
void compute_follow_non_terminal(NON_TERMINAL_LIST non_terminal_list);
void display_follow(NON_TERMINAL_LIST non_terminal_list);


// Functions for parse table
void populate_parse_table(NON_TERMINAL_LIST non_terminal_list, NON_TERMINAL non_terminal, RULE rule);
void compute_parse_table(NON_TERMINAL_LIST non_terminal_list);
void display_parse_table(NON_TERMINAL_LIST non_terminal_list);

//Functions for parsing
void print_error(LEX_OUT lexer_output, int i);
void add_child(TREENODE parent, TREENODE child);
void parse(Stack* stack, NON_TERMINAL_LIST non_terminal_list, LEX_OUT lexer_output);
void display_parse_tree(TREENODE root, FILE* parse_fp);
void destroy_tree(TREENODE root);

void lexer_and_parser(char** token_to_string_local, HASHMAP string_to_token_local, FILE* prog_fp, FILE* parse_fp);



#endif