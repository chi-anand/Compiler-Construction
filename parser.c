// Group No. : 13
// Adarsh Goel 2020B3A70821P
// Chinmay Anand 2020B3A70800P
// Arjoo Kumari 2020B3A70770P
// Mehak Agarwal 2020B3A70868P
// Jay Prakash Mundhra 2020B3A70799P
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "parserDef.h"
#include "lexer.h"
#include "stack.h"
#include "stdbool.h"
#include "tree.h"
#include "hashMap.h"
#include "global.h"

char** token_to_string;
HASHMAP string_to_token;
HASHMAP non_terminal_to_index;
GRAMMAR grammar;
// --------------------------- GRAMMAR.H functions----------------------------------- ----------------------


// Function for initialising grammar
GRAMMAR initialise_grammar()
{
    GRAMMAR grammar = (GRAMMAR) calloc(1, sizeof(struct grammar));
    grammar -> size = 0;
    grammar -> capacity = 1;
    (grammar -> rules) = (RULE *) calloc(grammar -> capacity, sizeof(RULE));
    return grammar;
}

// Function to insert production rule unit into single unit and return the tail
RULE insert_production_rule_unit(RULE rule_tail, char* production_rule_unit)
{
    RULE new_rule_unit = (RULE) calloc(1, sizeof(struct rule_unit));
    new_rule_unit -> production_rule_unit = (char *) calloc(strlen(production_rule_unit) + 1, sizeof(char));
    strcpy(new_rule_unit -> production_rule_unit, production_rule_unit);
    new_rule_unit -> next = NULL;
    if(rule_tail != NULL)
        rule_tail -> next = new_rule_unit;
    
    return new_rule_unit;
}

// Function for getting rule from line
RULE get_rule(char* line)
{
    // define the single rule variable
    RULE rule_head = NULL;
    RULE rule_tail = NULL;
    
    // define production rule atoms
    char* production_rule_unit;

    production_rule_unit = strtok(line, " \n");

    // read the line word by word
    while(production_rule_unit != NULL)
    {
        // insert the production rule unit into rule
        rule_tail = insert_production_rule_unit(rule_tail, production_rule_unit);
        if(rule_head == NULL)
            rule_head = rule_tail;
        production_rule_unit = strtok(NULL, " \n");
    }
    return rule_head;
}

// function to insert rule into grammar
void insert_rule(GRAMMAR grammar,RULE rule)
{
    if(grammar -> size == grammar -> capacity)
    {
        (grammar -> rules) = (RULE *) realloc(grammar -> rules, sizeof(RULE) * grammar -> capacity * 2);
        memset(grammar -> rules + grammar -> size, 0, sizeof(RULE) * grammar -> capacity);
        grammar -> capacity = grammar -> capacity * 2;
    }
    (grammar -> rules)[grammar -> size] = rule;
    grammar -> size = grammar -> size + 1;
}

// Function to preprocess grammar
void preprocess_grammar()
{
    // Define file pointer to program
    FILE *grammar_fp;

    // opening grammar file
    grammar_fp = fopen("grammar.txt", "r");
    if(!grammar_fp)
    {
        printf("Error opening file \n");
        exit(0);
    }

    // define line read variable
    char* line;
    line = (char *) calloc(256, sizeof(char));

    // initialise grammar variable
    grammar = initialise_grammar();

    // read the grammar.txt line by line
    while(fgets(line, sizeof(char) * 256, grammar_fp))
    {
        RULE rule = get_rule(line);
        insert_rule(grammar, rule);
    }
    fclose(grammar_fp);
}

// function to print grammar
void display_grammar()
{
    for(int i = 0; i < grammar -> size; ++i)
    {
        RULE temp = (grammar -> rules)[i];
        while(temp != NULL)
        {
            printf("%s ", temp -> production_rule_unit);
            temp = temp -> next;
        }
        printf("\n");
    }
}


// function to destroy grammar
void destroy_grammar()
{
    for(int i = 0; i < grammar -> size; ++i)
    {
        RULE prev = (grammar -> rules)[i];
        RULE curr = prev -> next;
        while(curr != NULL)
        {
            free(prev);
            prev = curr;
            curr = curr -> next;
        }
        free(prev);
    }

    free(grammar -> rules);
    free(grammar);
}

// ---------------------------------------------------------------------------------------------------------


//-----------------------non terminal preprocessing functions ------------------------------------------------


// Function to insert non terminal into non terminal list
void insert_non_terminal(NON_TERMINAL_LIST non_terminal_list, char* non_terminal)
{
    if(non_terminal_list -> size == non_terminal_list -> capacity)
    {
        non_terminal_list -> enteries = (NON_TERMINAL *) realloc(non_terminal_list -> enteries, sizeof(NON_TERMINAL) * non_terminal_list -> capacity * 2);
        memset(non_terminal_list -> enteries + non_terminal_list -> size, 0,  sizeof(NON_TERMINAL) * non_terminal_list -> capacity);
        non_terminal_list -> capacity = non_terminal_list -> capacity * 2;
    }
    (non_terminal_list -> enteries)[non_terminal_list -> size] = (NON_TERMINAL) calloc(1,sizeof(struct non_terminal));
    (non_terminal_list -> enteries)[non_terminal_list -> size] -> name = non_terminal;
    (non_terminal_list -> enteries)[non_terminal_list -> size] -> first_size = 0;
    (non_terminal_list -> enteries)[non_terminal_list -> size] -> first_capacity = 1;
    (non_terminal_list -> enteries)[non_terminal_list -> size] -> follow_size = 0;
    (non_terminal_list -> enteries)[non_terminal_list -> size] -> follow_capacity = 1;
    (non_terminal_list -> enteries)[non_terminal_list -> size] -> rule_size = 0;
    (non_terminal_list -> enteries)[non_terminal_list -> size] -> rule_capacity = 1;
    (non_terminal_list -> enteries)[non_terminal_list -> size] -> first = (int *) calloc(1,sizeof(int));
    (non_terminal_list -> enteries)[non_terminal_list -> size] -> follow = (int *) calloc(1, sizeof(int));
    (non_terminal_list -> enteries)[non_terminal_list -> size] -> associated_rules = (RULE *) calloc(1, sizeof(RULE));
    (non_terminal_list -> enteries)[non_terminal_list -> size] -> nullable = 0;
    (non_terminal_list -> enteries)[non_terminal_list -> size] -> is_computed_first = 0;
    (non_terminal_list -> enteries)[non_terminal_list -> size] -> is_computed_follow = 0;
    (non_terminal_list -> enteries)[non_terminal_list -> size] -> parse_table = (RULE *) calloc(NO_OF_TERMINALS, sizeof(RULE));
    non_terminal_list -> size = non_terminal_list -> size + 1;
}

// Function to insert associated rules into non terminal list
void insert_associated_rules(RULE rule, NON_TERMINAL_LIST non_terminal_list, int index)
{
    if((non_terminal_list -> enteries)[index] -> rule_size == (non_terminal_list -> enteries)[index] -> rule_capacity)
    {
        (non_terminal_list -> enteries)[index] -> associated_rules = (RULE *) realloc((non_terminal_list -> enteries)[index] -> associated_rules, sizeof(RULE) * (non_terminal_list -> enteries)[index] -> rule_capacity * 2);
        memset((non_terminal_list -> enteries)[index] -> associated_rules + (non_terminal_list -> enteries)[index] -> rule_size, 0, sizeof(RULE) * (non_terminal_list -> enteries)[index] -> rule_capacity);
        (non_terminal_list -> enteries)[index] -> rule_capacity = (non_terminal_list -> enteries)[index] -> rule_capacity * 2;
    }
    (non_terminal_list -> enteries)[index] -> associated_rules[(non_terminal_list -> enteries)[index] -> rule_size] = rule;
    if(strcmp("eps", (rule -> next -> next) -> production_rule_unit)== 0)
    { 
        (non_terminal_list -> enteries)[index] -> nullable = 1;
    }
    (non_terminal_list -> enteries)[index] -> rule_size = (non_terminal_list -> enteries)[index] -> rule_size + 1;

}

// Function to preprocess non-terminal
void preprocess_non_terminal_list(GRAMMAR grammar, NON_TERMINAL_LIST non_terminal_list)
{
    non_terminal_to_index = (HASHMAP) calloc(1, sizeof(struct hashMap));
    initializeHashMap(non_terminal_to_index); 
     
    for(int i = 0; i < grammar -> size; ++i)
    {
        int index = search(non_terminal_to_index, (grammar -> rules)[i] -> production_rule_unit);
        if(index == -1)
        {
            index = non_terminal_list -> size;
            insert_non_terminal(non_terminal_list, (grammar -> rules)[i] -> production_rule_unit);
            insert(non_terminal_to_index, (grammar -> rules)[i] -> production_rule_unit, index);
        }
        insert_associated_rules((grammar -> rules)[i], non_terminal_list, index);
    }
        
    
}

// Function to display non terminal list
void display_non_terminal_list(NON_TERMINAL_LIST non_terminal_list)
{
    for(int i = 0; i < non_terminal_list -> size; ++i)
    {
        for(int j = 0; j < (non_terminal_list -> enteries)[i] -> rule_size; ++j)
        {
            RULE temp = ((non_terminal_list -> enteries)[i] -> associated_rules)[j];
            while(temp != NULL)
            {
                printf("%s ", temp -> production_rule_unit);
                temp = temp -> next;
            }
            printf("\n");
        }
    }
}

// Function to destroy non terminal list
void destroy_non_terminal_list(NON_TERMINAL_LIST non_terminal_list)
{
    for(int i = 0; i < non_terminal_list -> size; ++i)
    {
        free((non_terminal_list -> enteries)[i] -> first);
        free((non_terminal_list -> enteries)[i] -> follow);
        free((non_terminal_list -> enteries)[i] -> associated_rules);
        free((non_terminal_list -> enteries)[i] -> parse_table);
    }
    free(non_terminal_list -> enteries);
    free(non_terminal_list);
}

// Function to initialise non terminal list
NON_TERMINAL_LIST initialise_non_terminal_list()
{
    NON_TERMINAL_LIST non_terminal_list  = (NON_TERMINAL_LIST) calloc(1, sizeof(struct non_terminal_list));
    non_terminal_list -> size = 0;
    non_terminal_list -> capacity = 1;
    non_terminal_list -> enteries = (NON_TERMINAL *) calloc(non_terminal_list -> capacity, sizeof(NON_TERMINAL) );
    return non_terminal_list;
}

//--------------------------------------------------------------------------------------------------------




// ------------------------ First functions --------------------------------------------------------------

// Function to check whether string is terminal or not
int is_terminal(char* production_rule_unit)
{
    if(production_rule_unit[0] == '<')
        return 0;
    else
        return 1;
}

// Function to insert first
void insert_first(NON_TERMINAL non_terminal, int terminal)
{
    
    if(non_terminal-> first_size == non_terminal -> first_capacity)
    {
        non_terminal -> first = (int *) realloc(non_terminal-> first, sizeof(int) * non_terminal -> first_capacity * 2);
        memset(non_terminal -> first + non_terminal -> first_size, 0, sizeof(int) * non_terminal -> first_capacity);
        non_terminal -> first_capacity = non_terminal-> first_capacity * 2;
    }
    non_terminal -> first[non_terminal-> first_size] = terminal;
    non_terminal -> first_size = non_terminal -> first_size + 1;
}

// Function to append first 
void append_first(NON_TERMINAL non_terminal_dest, NON_TERMINAL non_terminal_src)
{
    for(int i = 0; i < non_terminal_src -> first_size; ++i)
        insert_first(non_terminal_dest, (non_terminal_src -> first)[i]);
}

// function to compute first for a non terminal
void compute_first(NON_TERMINAL_LIST non_terminal_list, NON_TERMINAL non_terminal)
{
    int global_nullable = non_terminal -> nullable;
    int local_nullable = 0;
    for(int i = 0; i < non_terminal -> rule_size; ++i)
    {
        RULE temp = (non_terminal -> associated_rules)[i];
        temp = temp -> next -> next;
        while(temp != NULL)
        {
            if(is_terminal(temp -> production_rule_unit) == 1)
            {
                
                if(strcmp("eps", temp -> production_rule_unit) == 0)
                    break;
                insert_first(non_terminal, search(string_to_token, temp -> production_rule_unit));
                local_nullable = 0;
                break;
            }
            else
            {
                int index_src = search(non_terminal_to_index, temp -> production_rule_unit);
                NON_TERMINAL non_terminal_src = (non_terminal_list -> enteries)[index_src];

                if(non_terminal_src -> is_computed_first != 1)
                    compute_first(non_terminal_list, non_terminal_src);

                append_first(non_terminal, non_terminal_src);

                if(non_terminal_src -> nullable == 1)
                    local_nullable = 1;
                else
                {
                    local_nullable = 0;
                    break;
                }
                    
            }
            temp = temp -> next;
        }
        if(local_nullable == 1)
            global_nullable = 1;
    }
    non_terminal -> nullable = global_nullable;
    non_terminal -> is_computed_first = 1;

}

// Function to compute first for all terminals
void compute_first_non_terminal(NON_TERMINAL_LIST non_terminal_list)
{
    for(int i = 0; i < non_terminal_list -> size; ++i)
    {
        if((non_terminal_list -> enteries)[i] -> is_computed_first == 0)
            compute_first(non_terminal_list, (non_terminal_list -> enteries)[i]);
            
    }
}

// function to display first
void display_first(NON_TERMINAL_LIST non_terminal_list)
{
    for(int i = 0; i < non_terminal_list -> size; ++i)
    {
        printf("%s : ", (non_terminal_list -> enteries)[i] -> name);
        for(int j = 0; j < (non_terminal_list -> enteries)[i] -> first_size; ++j)
        {
            printf("%s ", token_to_string[((non_terminal_list -> enteries)[i] -> first)[j]]);
        }
        if((non_terminal_list -> enteries)[i] -> nullable == 1)
            printf("eps ");
        printf("\n");
    }
}

// ------------------------------------------------------------------------------------------------------------




// -------------------------------- Follow functions ---------------------------------------------------------


int is_nullable_beta(NON_TERMINAL_LIST non_terminal_list, RULE beta)
{
    RULE temp = beta;
    int nullable = 1;
    while(temp != NULL)
    {
        if(is_terminal(temp -> production_rule_unit) == 1)
        {
            nullable = 0;
            break;
        }
        else
        {
            int index_beta = search(non_terminal_to_index, temp -> production_rule_unit);
            NON_TERMINAL non_terminal_beta = (non_terminal_list -> enteries)[index_beta];
            // if non terminal  beta is not nullable
            if(non_terminal_beta -> nullable == 0)
            {
                nullable = 0;
                break;
            }
                
        }
        temp = temp -> next;
    }
    return nullable;
}

int* compute_first_beta(NON_TERMINAL_LIST non_terminal_list, RULE beta)
{
    int* first_beta = (int *) calloc( NO_OF_TERMINALS, sizeof(int));
    RULE temp = beta;
    while(temp != NULL)
    {
        if(is_terminal(temp -> production_rule_unit) == 1)
        {
            first_beta[search(string_to_token, temp -> production_rule_unit)] = 1;
            break;
        }
        else
        {
            int index_beta = search(non_terminal_to_index, temp -> production_rule_unit);
            NON_TERMINAL non_terminal_beta = (non_terminal_list -> enteries)[index_beta];
            for(int i = 0; i < non_terminal_beta -> first_size; ++i)
                first_beta[(non_terminal_beta -> first)[i]] = 1;

            // if non terminal  beta is not nullable
            if(non_terminal_beta -> nullable == 0)
                break;
        }
        temp = temp -> next;
    }
    return first_beta;
}

void insert_follow(NON_TERMINAL non_terminal, int terminal)
{
    if(non_terminal -> follow_size == non_terminal -> follow_capacity)
    {
        non_terminal -> follow = (int *) realloc(non_terminal -> follow, sizeof(int) * non_terminal -> follow_capacity * 2);
        memset(non_terminal -> follow + non_terminal -> follow_size, 0, sizeof(int) * non_terminal -> follow_capacity);
        non_terminal -> follow_capacity = non_terminal -> follow_capacity * 2;
    }
    (non_terminal -> follow)[non_terminal -> follow_size] = terminal;
    non_terminal -> follow_size = non_terminal -> follow_size + 1; 
}


void append_follow(NON_TERMINAL non_terminal, int* first_beta)
{
    for(int i = 0; i < NO_OF_TERMINALS; ++i)
    {
        if(first_beta[i] == 1)
        {
            int present = 0;
            for(int j = 0; j < non_terminal -> follow_size; ++j)
            {
                if((non_terminal -> follow)[j] == i)
                {
                    present = 1;
                    break;
                }
            }
            if(present == 0)
                insert_follow(non_terminal, i);
        }
    }
}


void compute_follow(NON_TERMINAL_LIST non_terminal_list, NON_TERMINAL non_terminal, int** marked)
{
    int index_A = search(non_terminal_to_index, non_terminal -> name);
    for(int i = 0; i < non_terminal -> rule_size; ++i)
    {
        RULE temp = (non_terminal -> associated_rules)[i];
        temp = temp -> next -> next;
        while(temp != NULL)
        {
            
            if(is_terminal(temp -> production_rule_unit) == 0)
            {
                
                int index_B = search(non_terminal_to_index, temp -> production_rule_unit);

                // rule A -> alpha B beta
                if(temp -> next != NULL )
                {
                    // calculate first of beta
                    int* first_beta = compute_first_beta(non_terminal_list, temp -> next);
                    append_follow((non_terminal_list -> enteries)[index_B], first_beta);

                    free(first_beta);

                    // if first of beta is nullable
                    if(is_nullable_beta(non_terminal_list, temp -> next) == 1)
                        marked[index_B][index_A] = 1;
                }
                // case A -> alpha B
                else
                    marked[index_B][index_A] = 1;
            }
            temp = temp -> next;
        }
    }
}

int  copy_follow(NON_TERMINAL non_terminal_dest, NON_TERMINAL non_terminal_src)
{
    int changed = 0;
    for(int i = 0; i < non_terminal_src -> follow_size; ++i)
    {
        int present = 0;
        for(int j = 0; j < non_terminal_dest -> follow_size; ++j)
        {
            if((non_terminal_dest -> follow)[j] == (non_terminal_src -> follow)[i])
            {
                present = 1;
                break;
            }
        }
        if(present == 0)
        {
            insert_follow(non_terminal_dest, (non_terminal_src -> follow)[i]);
            changed = 1;
        }
            
    }
    return changed;
}

// Function for computing final follow using dp
void final_follow(NON_TERMINAL_LIST non_terminal_list, int** marked)
{
    while(1)
    {
        int changed = 0;
        for(int i = 0; i < non_terminal_list -> size; ++i)
        {
            for(int j = 0; j < non_terminal_list -> size; ++j)
            {
                if(marked[i][j] == 1 && i != j)
                {
                    if(copy_follow((non_terminal_list -> enteries)[i], (non_terminal_list -> enteries)[j]) == 1)
                        changed = 1; 
                }
            }
        }
        if(changed == 0)
            break;
    }
}

// Function to compute follow set for all non terminal
void compute_follow_non_terminal(NON_TERMINAL_LIST non_terminal_list)
{
    // create marked variable to copy follow_A to follow_B
    int** marked = (int **) calloc(non_terminal_list -> size, sizeof(int *));
    for(int i = 0; i < non_terminal_list -> size; ++i)
    {
        marked[i] = (int *) calloc( non_terminal_list -> size, sizeof(int));
        memset(marked[i], 0, sizeof(int) * non_terminal_list -> size);
    }


    //  add $ to follow of start symbol
    insert_follow((non_terminal_list -> enteries)[0], 0);

    // compute follow for each non terminal
    for(int i = 0; i < non_terminal_list -> size; ++i)
        compute_follow(non_terminal_list, (non_terminal_list -> enteries)[i], marked);

    // compute the final follow sets
    final_follow(non_terminal_list, marked);

    // free the memory taken by marked  
    for(int i = 0; i < non_terminal_list -> size; ++i)
        free(marked[i]);
    free(marked);
}

// function to display follow
void display_follow(NON_TERMINAL_LIST non_terminal_list)
{
    for(int i = 0; i < non_terminal_list -> size; ++i)
    {
        printf("%s : ", (non_terminal_list -> enteries)[i] -> name);
        for(int j = 0; j < (non_terminal_list -> enteries)[i] -> follow_size; ++j)
        {
            printf("%s ", token_to_string[((non_terminal_list -> enteries)[i] -> follow)[j]]);
        }
        printf("\n");
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------



// ---------------------------------Parsing table----------------------------------------------------------------------------------

// function to populate parse table for each rule
void populate_parse_table(NON_TERMINAL_LIST non_terminal_list, NON_TERMINAL non_terminal, RULE rule)
{
    

    // rule A -> eps
    if(strcmp(rule -> next -> next -> production_rule_unit, "eps") == 0)
    {
        for(int i = 0; i < non_terminal -> follow_size; ++i)
        {
            (non_terminal -> parse_table)[(non_terminal -> follow)[i]] = rule;
        }
    }
    // rule A -> alpha 
    else
    {
        int* first_alpha;
        int is_first_nullable;
        first_alpha = compute_first_beta(non_terminal_list, rule -> next -> next);
        
        
        is_first_nullable = is_nullable_beta(non_terminal_list, rule -> next -> next);
    
        for(int i = 0; i < NO_OF_TERMINALS; ++i)
        {
            if(first_alpha[i] == 1)
            {
                (non_terminal -> parse_table)[i] = rule;
            }
        }
        

        if(is_first_nullable == 1)
        {
            for(int i = 0; i < non_terminal -> follow_size; ++i)
            {
                (non_terminal -> parse_table)[(non_terminal -> follow)[i]] = rule;
            }
        }

    }
    
}

// function for creating parse table
void compute_parse_table(NON_TERMINAL_LIST non_terminal_list)
{
    for(int i = 0; i < non_terminal_list -> size; ++i)
    {
        memset((non_terminal_list -> enteries)[i] -> parse_table, 0, sizeof(RULE) * NO_OF_TERMINALS);
        for(int j = 0; j < (non_terminal_list -> enteries)[i] -> rule_size; ++j)
        {
            populate_parse_table(non_terminal_list, (non_terminal_list -> enteries)[i], ((non_terminal_list -> enteries)[i] -> associated_rules)[j]);
        }
    }
}


// print parse table
void display_parse_table(NON_TERMINAL_LIST non_terminal_list)
{
    for(int i = 0; i < non_terminal_list -> size; ++i)
    {
        printf("%s\n", (non_terminal_list -> enteries)[i] -> name);
        for(int j = 0; j < NO_OF_TERMINALS; ++j)
        {
            if(((non_terminal_list -> enteries)[i] -> parse_table)[j] != NULL)
            {
                
                printf("%s : ", token_to_string[j]);
                
                RULE temp = ((non_terminal_list -> enteries)[i] -> parse_table)[j];
                while(temp != NULL)
                {
                    printf("%s ", temp -> production_rule_unit);
                    temp = temp -> next;
                }
                
                printf("\n");
            }
        }
        

        printf("\n--------------------------------------------------------------------------------\n");
    }
}

// -----------------------------------------------------------------------------------------------------------------



// --------------------parse function--------------------------------------------------------------------------------

void print_error(LEX_OUT lexer_output, int i)
{
     if((lexer_output -> enteries)[i] -> token == TK_ERROR1)
    {
        printf("Line no. %d : Error : Unknown pattern <%s>\n", (lexer_output -> enteries)[i] -> line_num, (lexer_output -> enteries)[i] -> lexeme);
    }
    else if((lexer_output -> enteries)[i] -> token == TK_ERROR2)
    {
        printf("Line no. %d : Error : Funtion identifier is longer than the prescribed length of 30 chararcters.\n", (lexer_output -> enteries)[i] -> line_num);
    }
    else if((lexer_output -> enteries)[i] -> token == TK_ERROR3)
    {
        printf("Line no. %d : Error : Variable identifier is longer than the prescribed length of 20 chararcters.\n", (lexer_output -> enteries)[i] -> line_num);
    }
    else if((lexer_output -> enteries)[i] -> token == TK_ERROR4)
    {
        printf("Line no. %d : Error : Unknown symbol <%s>\n", (lexer_output -> enteries)[i] -> line_num, (lexer_output -> enteries)[i] -> lexeme);
    }
}
void add_child(TREENODE parent, TREENODE child)
{
    if(parent -> size == parent -> capacity)
    {
        parent -> children = (TREENODE *) realloc(parent -> children, sizeof(TREENODE) * parent -> capacity * 2);
        memset(parent -> children + parent -> size, 0,sizeof(TREENODE) * parent -> capacity  );
        parent -> capacity = parent -> capacity * 2;
    }
    (parent -> children)[parent -> size] = child;
    parent -> size = parent -> size + 1;
}


void parse(Stack* stack, NON_TERMINAL_LIST non_terminal_list, LEX_OUT lexer_output)
{
    
    TREENODE top_of_stack = *top(stack);
    int i = 0;
    while(i != lexer_output -> size && strcmp(top_of_stack -> symbol, "$") != 0)
    {
        if((lexer_output -> enteries)[i] -> token == TK_ERROR1 || (lexer_output -> enteries)[i] -> token == TK_ERROR2 || (lexer_output -> enteries)[i] -> token == TK_ERROR3 || (lexer_output -> enteries)[i] -> token == TK_ERROR4)
        {
            print_error(lexer_output, i);
            ++i;
            continue;
        }
       
        char* current_lexer_char = token_to_string[(lexer_output -> enteries)[i] -> token];
        if(top_of_stack -> token == TK_EPS)
        {
            
            top_of_stack -> lexeme = "eps";
            pop(stack);
        }
        else if(top_of_stack -> isLeaf == 1 && strcmp(token_to_string[top_of_stack -> token], current_lexer_char) == 0 )
        {
            
            top_of_stack -> line_num = (lexer_output -> enteries)[i] -> line_num;
            top_of_stack -> lexeme = (lexer_output -> enteries)[i] -> lexeme;
            pop(stack);
            ++i;
        }
        else if(top_of_stack -> isLeaf == 1)
        {
            printf("Line no. %d : Error : The token %s for lexeme %s does not match with the expected token %s\n", (lexer_output -> enteries)[i] -> line_num,  current_lexer_char,(lexer_output -> enteries)[i] -> lexeme,  token_to_string[top_of_stack -> token]);
            pop(stack);
        }
        else if(((non_terminal_list -> enteries)[search(non_terminal_to_index, top_of_stack -> symbol)] -> parse_table)[(lexer_output -> enteries)[i] -> token] == NULL)
        {
            int synch_flag = 0;
            for(int j = 0; j < (non_terminal_list -> enteries)[search(non_terminal_to_index, top_of_stack -> symbol)] -> follow_size; ++j)
            {
                if(((non_terminal_list -> enteries)[search(non_terminal_to_index, top_of_stack -> symbol)] -> follow)[j] == (lexer_output -> enteries)[i] -> token)
                {
                    synch_flag = 1;
                    break;
                }
            }
            printf("Line no. %d : Error : Invalid Token %s encountered with value %s stack top %s\n", (lexer_output -> enteries)[i] -> line_num, current_lexer_char, (lexer_output -> enteries)[i] -> lexeme, top_of_stack -> symbol);
            int curr_token = (lexer_output -> enteries)[i] -> token;
            if(synch_flag == 1 || curr_token == TK_END || curr_token == TK_ENDIF || curr_token == TK_ENDRECORD || curr_token == TK_ENDUNION || curr_token == TK_ENDWHILE || curr_token == TK_IF || curr_token == TK_READ || curr_token == TK_WRITE || curr_token == TK_WHILE || curr_token == TK_CALL || curr_token == TK_TYPE)
            {
                pop(stack);
                top_of_stack = *top(stack);
                continue;
            }
            ++i;
            while(i != lexer_output -> size)
            {
                curr_token = (lexer_output -> enteries)[i] -> token;
                if(curr_token == TK_ERROR1 || curr_token == TK_ERROR2 || curr_token == TK_ERROR3 || curr_token == TK_ERROR4)
                {
                    print_error(lexer_output, i);
                    ++i;
                    continue;
                }
                if(((non_terminal_list -> enteries)[search(non_terminal_to_index, top_of_stack -> symbol)] -> parse_table)[curr_token] != NULL)
                {
                    break;
                }
                synch_flag = 0;
                for(int k = 0; k < (non_terminal_list -> enteries)[search(non_terminal_to_index, top_of_stack -> symbol)] -> follow_size; ++k)
                {
                    if(((non_terminal_list -> enteries)[search(non_terminal_to_index, top_of_stack -> symbol)] -> follow)[k] == (lexer_output -> enteries)[i] -> token)
                    {
                        synch_flag = 1; 
                        break;
                    }
                }
                if(synch_flag == 1 || curr_token == TK_END || curr_token == TK_ENDIF || curr_token == TK_ENDRECORD || curr_token == TK_ENDUNION || curr_token == TK_ENDWHILE || curr_token == TK_IF || curr_token == TK_READ || curr_token == TK_WRITE || curr_token == TK_WHILE || curr_token == TK_CALL|| curr_token == TK_TYPE)
                {
                    pop(stack);
                    break;
                }
                ++i;
            }
            
        }
        else
        {
            pop(stack);
            
            RULE temp = ((non_terminal_list -> enteries)[search(non_terminal_to_index, top_of_stack -> symbol)] -> parse_table)[(lexer_output -> enteries)[i] -> token];
            //printf("%s %s ", temp -> production_rule_unit, temp -> next -> production_rule_unit);
            
            temp = temp -> next -> next;
            Stack* temp_stack = newStack();
            while(temp != NULL)
            {
                //printf("%s ", temp -> production_rule_unit);
                TREENODE child = (TREENODE) calloc(1, sizeof(struct treeNode));
                if(is_terminal(temp -> production_rule_unit) == 1)
                {
                    child -> lexeme = "---";
                    if(strcmp(temp -> production_rule_unit, "eps") != 0)
                        child -> token = search(string_to_token, temp -> production_rule_unit);
                    else
                        child -> token = TK_EPS;
                    child -> isLeaf = 1;
                    child -> line_num = (lexer_output -> enteries)[i] -> line_num;
                    child -> parent = top_of_stack;
                    child -> symbol = "---";
                    child -> children = NULL;
                }
                else
                {
                    child -> lexeme = "---";
                    child -> token = -1;
                    child -> isLeaf = 0;
                    child -> line_num = (lexer_output -> enteries)[i] -> line_num;;
                    child -> parent = top_of_stack;
                    child -> symbol = temp -> production_rule_unit;
                    child -> children = NULL;
                    child -> size = 0;
                    child -> capacity = 1;
                    child -> children = (TREENODE*)calloc(sizeof(TREENODE), 1);
                }
                add_child(top_of_stack, child);
                push(temp_stack, child);
                temp = temp -> next;
            }   
            
            while(!isEmpty(temp_stack))
            {
                push(stack, *top(temp_stack));
                pop(temp_stack);
            }
            freeStack(temp_stack);
            //printf("\n");
        }
        
        top_of_stack = *top(stack);
        

    }
}

void display_parse_tree(TREENODE root, FILE* parse_fp)
{   
    if(root == NULL)
        return;
    if(root -> token == TK_EPS)
    {
         if(root->parent == NULL) 
            fprintf(parse_fp, "%20s%10s%15s%15s%30s%20s%30s\n","---","---","EPSILON","---","<NOPARENT>","yes","---");
        else
           fprintf(parse_fp,"%20s%10s%15s%15s%30s%20s%30s\n","---","---","EPSILON","---",root -> parent -> symbol,"yes","---");
    }
    else if(root -> isLeaf == 1)
    {
        if(root -> token == TK_NUM || root -> token== TK_RNUM) 
            fprintf(parse_fp,"%20s%10d%15s%15s%30s%20s%30s\n",root -> lexeme, root -> line_num,token_to_string[root -> token], root -> lexeme, root -> parent -> symbol, "yes", "---");
        else
            fprintf(parse_fp,"%20s%10d%15s%15s%30s%20s%30s\n",root -> lexeme, root -> line_num,token_to_string[root -> token], "---", root -> parent -> symbol, "yes", "---");
    }
    else
    {
        display_parse_tree((root -> children)[0], parse_fp);
        if(strcmp(root -> symbol, "<program>") == 0)
            fprintf(parse_fp,"%20s%10s%15s%15s%30s%20s%30s\n","---","---","---","---","ROOT","no",root -> symbol);
        if(root -> parent == NULL) 
            fprintf(parse_fp,"%20s%10s%15s%15s%30s%20s%30s\n","---","---","---","---","<NOPARENT>","no",root -> symbol);
        else 
            fprintf(parse_fp,"%20s%10s%15s%15s%30s%20s%30s\n","---","---","---","---",root -> parent -> symbol,"no",root -> symbol);
        for(int i = 1; i < root -> size; ++i)
            display_parse_tree((root -> children)[i], parse_fp);
    } 
}

void destroy_tree(TREENODE root)
{
    if(root -> size == 0 || root -> isLeaf == 1)
    {
        free(root);
        return;
    }
        
    for(int i = 0; i < root -> size; ++i)
        destroy_tree((root -> children)[i]);
    free(root -> children);
    free(root);
}


void lexer_and_parser(char** token_to_string_local, HASHMAP string_to_token_local, FILE* prog_fp, FILE* parse_fp)
{

    // initialise global variable
    token_to_string = token_to_string_local;
    string_to_token = string_to_token_local;
    

    // preprocess the grammar
    preprocess_grammar();
    
    // initialise non terminal list
    NON_TERMINAL_LIST non_terminal_list = initialise_non_terminal_list();

    // preprocess non terminal
    preprocess_non_terminal_list(grammar, non_terminal_list);
        
    // compute first for all non terminals
    compute_first_non_terminal(non_terminal_list);

    // Compute follow for all non terminals
    compute_follow_non_terminal(non_terminal_list);

    // create the parse table
    compute_parse_table(non_terminal_list);

    
    
    
    // start the parsing
    
    Stack* stack = newStack();
    TREENODE dollar = (TREENODE) calloc(1,sizeof(struct treeNode));
    TREENODE start = (TREENODE) calloc(1, sizeof(struct treeNode));
    dollar -> symbol = "$";
    start -> symbol = "<program>";
    start -> isLeaf = 0;
    start -> parent = NULL;

    push(stack, dollar);
    push(stack, start);
    LEX_OUT lexer_output = compute_tokens(token_to_string,0, prog_fp);
    parse(stack, non_terminal_list, lexer_output);

    display_parse_tree(start, parse_fp);
    

    // display the grammar and non terminal list
    //display_grammar();
    //display_non_terminal_list(non_terminal_list);
    //display_first(non_terminal_list);
    //display_follow(non_terminal_list);
    //display_parse_table(non_terminal_list);


    // destroy the various data structures
    destroy_grammar(); // ---IMP --- destroy grammar before non terminal list
    destroy_non_terminal_list(non_terminal_list);
    destroy_lex_out(lexer_output);
    deleteMap(non_terminal_to_index);
    freeStack(stack);
    destroy_tree(start);
}