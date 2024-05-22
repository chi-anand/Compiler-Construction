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
#include "lexer.h"
#include "symbolTable.h"
#include "global.h"
#define buffer_size 1024

// Function for incrementing foward pointer and return new forward pointer buffer
char *increment_pointer(int *fwd_pointer, char *buf1, char *buf2, char *fwd_buf, int* char_read, FILE* prog_fp, int *refill_flag)
{
    char *new_fwd_buf = fwd_buf;
    if(*fwd_pointer == buffer_size / 2 - 1)
    {
        if(fwd_buf == buf1)
        {
            if(*refill_flag == 1)
                *char_read = fread(buf2, sizeof(char), buffer_size / 2, prog_fp);
            new_fwd_buf = buf2;
        } 
        else if(fwd_buf == buf2)
        {
            if(*refill_flag == 1)
                *char_read = fread(buf1, sizeof(char), buffer_size / 2, prog_fp);
            new_fwd_buf = buf1;
        }
        *refill_flag = 1;
    }
    *fwd_pointer = (*fwd_pointer + 1) % (buffer_size / 2);
    return new_fwd_buf;
}

// Function for decrementing pointer
char *decrement_pointer(int *fwd_pointer, char *buf1, char *buf2, char *fwd_buf, int *refill_flag)
{
    char *new_fwd_buf = fwd_buf;
    if(*fwd_pointer == 0)
    {
        if(fwd_buf == buf1)
            new_fwd_buf = buf2;
        else    
            new_fwd_buf = buf1;
        *refill_flag = 0;
    }
    *fwd_pointer = *fwd_pointer - 1;
    if(*fwd_pointer < 0)
        *fwd_pointer = *fwd_pointer + buffer_size / 2;
    return new_fwd_buf;
}

// Function for getting lexeme from twin buffer.
char *get_lexeme(int* fwd_pointer, int* beg_pointer, char* fwd_buf, char* beg_buf)
{
    char* lexeme;
    if(fwd_buf == beg_buf)
    {
        lexeme = (char *) calloc((*fwd_pointer - *beg_pointer + 1), sizeof(char));
        for(int i = 0; i < *fwd_pointer - *beg_pointer; ++i)
            lexeme[i] = beg_buf[i + *beg_pointer];
        lexeme[*fwd_pointer - *beg_pointer] = '\0';
    }
    else
    {
        lexeme = (char*) calloc((buffer_size / 2 + *fwd_pointer - *beg_pointer + 1), sizeof(char));
        for(int i = 0; i < buffer_size / 2 - * beg_pointer; ++i)
            lexeme[i] = beg_buf[i + *beg_pointer];

        for(int j = buffer_size / 2 - *beg_pointer, k = 0; j < buffer_size / 2 + *fwd_pointer - *beg_pointer; ++j, ++k)
            lexeme[j] = fwd_buf[k];
        
        lexeme[buffer_size / 2 + *fwd_pointer - *beg_pointer] = '\0';
    }
    return lexeme;
}

// Function for populating symbol table
SYM_TABLE populate_symbol_table()
{
    SYM_TABLE symbol_table = (SYM_TABLE) calloc(1, sizeof(struct sym_table));
    symbol_table -> size = 28;
    symbol_table -> capacity = 28;
    (symbol_table -> enteries) = (SYM_ROW *) calloc(symbol_table -> capacity, sizeof(SYM_ROW));

    for(int i = 0; i < 28; ++i)
        (symbol_table -> enteries)[i] = (SYM_ROW) calloc(1,sizeof(struct sym_table_row));

    // Fill the symbol table with keywords
    (symbol_table -> enteries)[0] -> lexeme = "with";
    (symbol_table -> enteries)[0] -> token = TK_WITH;

    (symbol_table -> enteries)[1] -> lexeme = "parameters";
    (symbol_table -> enteries)[1] -> token = TK_PARAMETERS;


    (symbol_table -> enteries)[2] -> lexeme = "end";
    (symbol_table -> enteries)[2] -> token = TK_END;

    (symbol_table -> enteries)[3] -> lexeme = "while";
    (symbol_table -> enteries)[3] -> token = TK_WHILE;

    (symbol_table -> enteries)[4] -> lexeme = "union";
    (symbol_table -> enteries)[4] -> token = TK_UNION;

    (symbol_table -> enteries)[5] -> lexeme = "endunion";
    (symbol_table -> enteries)[5] -> token = TK_ENDUNION;

    (symbol_table -> enteries)[6] -> lexeme = "definetype";
    (symbol_table -> enteries)[6] -> token = TK_DEFINETYPE;
    
    (symbol_table -> enteries)[7] -> lexeme = "as";
    (symbol_table -> enteries)[7] -> token = TK_AS;

    (symbol_table -> enteries)[8] -> lexeme = "type";
    (symbol_table -> enteries)[8] -> token = TK_TYPE;

    (symbol_table -> enteries)[9] -> lexeme = "_main";
    (symbol_table -> enteries)[9] -> token = TK_MAIN;

    (symbol_table -> enteries)[10] -> lexeme = "global";
    (symbol_table -> enteries)[10] -> token = TK_GLOBAL;

    (symbol_table -> enteries)[11] -> lexeme = "parameter";
    (symbol_table -> enteries)[11] -> token = TK_PARAMETER;

    (symbol_table -> enteries)[12] -> lexeme = "list";
    (symbol_table -> enteries)[12] -> token = TK_LIST;

    (symbol_table -> enteries)[13] -> lexeme = "input";
    (symbol_table -> enteries)[13] -> token = TK_INPUT;

    (symbol_table -> enteries)[14] -> lexeme = "output";
    (symbol_table -> enteries)[14] -> token = TK_OUTPUT;

    (symbol_table -> enteries)[15] -> lexeme = "int";
    (symbol_table -> enteries)[15] -> token = TK_INT;

    (symbol_table -> enteries)[16] -> lexeme = "real";
    (symbol_table -> enteries)[16] -> token = TK_REAL;

    (symbol_table -> enteries)[17] -> lexeme = "endwhile";
    (symbol_table -> enteries)[17] -> token = TK_ENDWHILE;

    (symbol_table -> enteries)[18] -> lexeme = "if";
    (symbol_table -> enteries)[18] -> token = TK_IF;

    (symbol_table -> enteries)[19] -> lexeme = "then";
    (symbol_table -> enteries)[19] -> token = TK_THEN;

    (symbol_table -> enteries)[20] -> lexeme = "endif";
    (symbol_table -> enteries)[20] -> token = TK_ENDIF;

    (symbol_table -> enteries)[21] -> lexeme = "read";
    (symbol_table -> enteries)[21] -> token = TK_READ;

    (symbol_table -> enteries)[22] -> lexeme = "write";
    (symbol_table -> enteries)[22] -> token = TK_WRITE;

    (symbol_table -> enteries)[23] -> lexeme = "return";
    (symbol_table -> enteries)[23] -> token = TK_RETURN;

    (symbol_table -> enteries)[24] -> lexeme = "call";
    (symbol_table -> enteries)[24] -> token = TK_CALL;

    (symbol_table -> enteries)[25] -> lexeme = "record";
    (symbol_table -> enteries)[25] -> token = TK_RECORD;

    (symbol_table -> enteries)[26] -> lexeme = "endrecord";
    (symbol_table -> enteries)[26] -> token = TK_ENDRECORD;

    (symbol_table -> enteries)[27] -> lexeme = "else";
    (symbol_table -> enteries)[27] -> token = TK_ELSE;

    return symbol_table;
}

// Function for initialising lexer output
LEX_OUT initialise_lexer_output()
{
    LEX_OUT lexer_output = (LEX_OUT) calloc(1, sizeof(struct lex_out));
    lexer_output -> size = 0;
    lexer_output -> capacity = 2;
    (lexer_output -> enteries) = (LEX_ROW *) calloc(lexer_output -> capacity, sizeof(LEX_ROW));
    return lexer_output;
}


// Function for lookup in symbol table
SYM_ROW lookup_symbol_table(SYM_TABLE symbol_table, char* lexeme)
{
    SYM_ROW result = NULL; 
    for(int i = 0; i < symbol_table -> size; ++i)
    {
        if(strcmp((symbol_table -> enteries)[i] -> lexeme , lexeme) == 0)
        {
            result = (symbol_table -> enteries)[i];
            break;
        }
    }
    return result;
}

// Function for inserting lexeme and token in symbol table
void insert_lexeme_token(SYM_TABLE symbol_table, char* lexeme, int token)
{
    
    if(symbol_table -> size == symbol_table -> capacity)
    {
        (symbol_table -> enteries) = (SYM_ROW *) realloc(symbol_table -> enteries, sizeof(SYM_ROW) * symbol_table -> capacity * 2);
        memset(symbol_table -> enteries + symbol_table -> size, 0, sizeof(SYM_ROW) * symbol_table -> capacity);
        symbol_table -> capacity = symbol_table -> capacity * 2;
    }
    (symbol_table -> enteries)[symbol_table -> size] = (SYM_ROW) calloc(1, sizeof(struct sym_table_row));
    (symbol_table -> enteries)[symbol_table -> size] -> lexeme = lexeme;
    (symbol_table -> enteries)[symbol_table -> size] -> token = token;
    symbol_table -> size = symbol_table -> size + 1;
    return;
}

// Function for inserting lexeme stream
void insert_lexeme_out(LEX_OUT lexer_output, char* lexeme, int token, int line_num)
{
    if(lexer_output -> size == lexer_output-> capacity)
    {
        (lexer_output-> enteries) = (LEX_ROW *) realloc(lexer_output -> enteries, sizeof(LEX_ROW) * lexer_output -> capacity * 2);
        memset(lexer_output -> enteries + lexer_output -> size, 0, sizeof(LEX_ROW) * lexer_output -> capacity);
        lexer_output -> capacity = lexer_output -> capacity * 2;
    }
    (lexer_output -> enteries)[lexer_output -> size] = (LEX_ROW) calloc(1, sizeof(struct lex_out_row));
    (lexer_output -> enteries)[lexer_output -> size] -> lexeme = lexeme;
    (lexer_output -> enteries)[lexer_output -> size] -> token = token;
    (lexer_output -> enteries)[lexer_output -> size] -> line_num = line_num;
    lexer_output -> size = lexer_output-> size + 1;
    return;
}

// Function to free memory for symbol table
void destroy_symbol_table(SYM_TABLE symbol_table)
{
    for(int i = 0; i < symbol_table -> size; ++i)
        free((symbol_table -> enteries)[i]);

    free(symbol_table -> enteries);
    free(symbol_table);
}

// Function to destroy lexer output
void destroy_lex_out(LEX_OUT lexer_output)
{
    for(int i = 0; i < lexer_output -> size; ++i)
    {
        if((lexer_output -> enteries)[i] -> token != TK_ERROR2 && (lexer_output -> enteries)[i] -> token != TK_ERROR3)
            free((lexer_output -> enteries)[i] -> lexeme);
    }
        
    
    for(int i = 0; i < lexer_output -> size; ++i)
        free((lexer_output -> enteries)[i]);

    free(lexer_output-> enteries);
    free(lexer_output);
}



// Function to display symbol table
void display_symbol_table(SYM_TABLE symbol_table, char** token_to_string)
{
    for(int i = 0; i < symbol_table -> size; ++i)
        printf("%s  %s\n", (symbol_table -> enteries)[i] -> lexeme, token_to_string[(symbol_table -> enteries)[i] -> token]);
}


// Function to display lexer output
void display_lexer_output(LEX_OUT lexer_output, char** token_to_string)
{
    for(int i = 0; i < lexer_output -> size; ++i)
        if((lexer_output-> enteries)[i] -> token > 0 && (lexer_output-> enteries)[i] -> token < 58)
            printf("%s  %s  %d\n", (lexer_output-> enteries)[i] -> lexeme, token_to_string[(lexer_output -> enteries)[i] -> token],(lexer_output -> enteries)[i] -> line_num);
}



LEX_OUT compute_tokens(char** token_to_string, int print_flag, FILE* prog_fp)
{
    

    // defining twin buffer. Define foward pointer buffer and begin pointer buffer
    char *buf1, *buf2, *fwd_buf, *beg_buf;  

    // allocating memory for buffers
    buf1 = (char *) calloc(buffer_size / 2, sizeof(char));
    buf2 = (char *) calloc(buffer_size / 2, sizeof(char));
    fwd_buf = buf1;
    beg_buf = buf1;


    // char_read maintains no. of characters read
    int* char_read;
    char_read = (int *) calloc(1,sizeof(int));

    // intialize begin pointer and forward pointer
    int *beg_pointer, *fwd_pointer;
    beg_pointer = (int *) calloc(1, sizeof(int));
    fwd_pointer = (int *) calloc(1, sizeof(int));
    *beg_pointer = 0;
    *fwd_pointer = 0;

    // read the contents into the buf1
    *char_read = fread(buf1, sizeof(char), buffer_size / 2, prog_fp);

    // initialise initial state
    int state = 0;

    //temporary variable to store lexeme and line number.
    char* lexeme;
    int line_num = 1;
    int flag = 0;

    // defining refill buffer flag
    int *refill_flag = (int *) calloc(1, sizeof(int));
    *refill_flag = 1;


    // define and populate symbol table and initialise global variables 
    SYM_TABLE symbol_table = populate_symbol_table();

    // initialise lexer output
    LEX_OUT lexer_output = initialise_lexer_output();



    // start the traversal of dfa for the program.
    while(1)
    {
        
        begin_switch:
        switch(state)
        {
            //start state.
            case 0:
                if(fwd_buf[*fwd_pointer] == ',')
                    state = 1;
                else if(fwd_buf[*fwd_pointer] == ';')
                    state = 2;
                else if(fwd_buf[*fwd_pointer] == ':')
                    state = 3;
                else if(fwd_buf[*fwd_pointer] == '.')
                    state = 4;
                else if(fwd_buf[*fwd_pointer] == '(')
                    state = 5;
                else if(fwd_buf[*fwd_pointer] == ')')
                    state = 6;
                else if(fwd_buf[*fwd_pointer] == '+')
                    state = 7;
                else if(fwd_buf[*fwd_pointer] == '-')
                    state = 8;
                else if(fwd_buf[*fwd_pointer] == '*')
                    state = 9;
                else if(fwd_buf[*fwd_pointer] == '/')
                    state = 10;
                else if(fwd_buf[*fwd_pointer] == '~')
                    state = 11;
                else if(fwd_buf[*fwd_pointer] == '=')
                    state = 12;
                else if(fwd_buf[*fwd_pointer] == '>')
                    state = 14;
                else if(fwd_buf[*fwd_pointer] == '!')
                    state = 17;
                else if(fwd_buf[*fwd_pointer] == '[')
                    state = 19;
                else if(fwd_buf[*fwd_pointer] == ']')
                    state = 20;
                else if(fwd_buf[*fwd_pointer] == '%')
                    state = 21;
                else if(fwd_buf[*fwd_pointer] == '&')
                    state = 22;
                else if(fwd_buf[*fwd_pointer] == '@')
                    state = 25;
                else if(fwd_buf[*fwd_pointer] == '<')
                    state = 28;
                else if(fwd_buf[*fwd_pointer] >= '0' && fwd_buf[*fwd_pointer] <= '9')
                    state = 34;
                else if(fwd_buf[*fwd_pointer] == '#')
                    state = 43;
                else if(fwd_buf[*fwd_pointer] == '_')
                    state = 46;
                else if(fwd_buf[*fwd_pointer] >= 'b' && fwd_buf[*fwd_pointer] <= 'd')
                    state = 50;
                else if(fwd_buf[*fwd_pointer] >= 'a' && fwd_buf[*fwd_pointer] <= 'z')
                    state = 51;
                else if(fwd_buf[*fwd_pointer] == '\t')
                    state = 56;
                else if(fwd_buf[*fwd_pointer] == ' ')
                    state = 57;
                else if(fwd_buf[*fwd_pointer] == '\n')
                    state = 58;
                else
                    state = 203; // denotes illegal character error 
                fwd_buf = increment_pointer(fwd_pointer, buf1, buf2, fwd_buf, char_read, prog_fp, refill_flag);
                goto begin_switch;

            // accept state for ,
            case 1:
                lexeme = get_lexeme(fwd_pointer, beg_pointer, fwd_buf, beg_buf);
                if(print_flag == 1)
                    printf("Line no. %d\t\tLexeme %s\t\tToken %s\n", line_num, lexeme, "TK_COMMA");
                if(lookup_symbol_table(symbol_table, lexeme) == NULL)
                    insert_lexeme_token(symbol_table, lexeme, TK_COMMA);
                insert_lexeme_out(lexer_output, lexeme, TK_COMMA, line_num);
                *beg_pointer = *fwd_pointer;
                beg_buf = fwd_buf;
                state = 0;
                break;

            // accept state for ;
            case 2:
                lexeme = get_lexeme(fwd_pointer, beg_pointer, fwd_buf, beg_buf);
                if(print_flag == 1)
                    printf("Line no. %d\t\tLexeme %s\t\tToken %s\n", line_num, lexeme, "TK_SEM");
                if(lookup_symbol_table(symbol_table, lexeme) == NULL)
                    insert_lexeme_token(symbol_table, lexeme, TK_SEM);
                insert_lexeme_out(lexer_output, lexeme, TK_SEM, line_num);
                *beg_pointer = *fwd_pointer;
                beg_buf = fwd_buf;
                state = 0;
                break;

            //accept state for :
            case 3:
                lexeme = get_lexeme(fwd_pointer, beg_pointer, fwd_buf, beg_buf);
                if(print_flag == 1)
                    printf("Line no. %d\t\tLexeme %s\t\tToken %s\n", line_num, lexeme, "TK_COLON");
                if(lookup_symbol_table(symbol_table, lexeme) == NULL)
                    insert_lexeme_token(symbol_table, lexeme, TK_COLON);
                insert_lexeme_out(lexer_output, lexeme, TK_COLON, line_num);
                *beg_pointer = *fwd_pointer;
                beg_buf = fwd_buf;
                state = 0;
                break;

            //accept state for .
            case 4:
                lexeme = get_lexeme(fwd_pointer, beg_pointer, fwd_buf, beg_buf);
                if(print_flag == 1)
                    printf("Line no. %d\t\tLexeme %s\t\tToken %s\n", line_num, lexeme, "TK_DOT");
                if(lookup_symbol_table(symbol_table, lexeme) == NULL)
                    insert_lexeme_token(symbol_table, lexeme, TK_DOT);
                insert_lexeme_out(lexer_output, lexeme, TK_DOT, line_num);
                *beg_pointer = *fwd_pointer;
                beg_buf = fwd_buf;
                state = 0;
                break;

            //accept state for (
            case 5:
                lexeme = get_lexeme(fwd_pointer, beg_pointer, fwd_buf, beg_buf);
                if(print_flag == 1)
                    printf("Line no. %d\t\tLexeme %s\t\tToken %s\n", line_num, lexeme, "TK_OP");
                if(lookup_symbol_table(symbol_table, lexeme) == NULL)
                    insert_lexeme_token(symbol_table, lexeme, TK_OP);
                insert_lexeme_out(lexer_output, lexeme, TK_OP, line_num);
                *beg_pointer = *fwd_pointer;
                beg_buf = fwd_buf;
                state = 0;
                break;

            //accept state for )
            case 6:
                lexeme = get_lexeme(fwd_pointer, beg_pointer, fwd_buf, beg_buf);
                if(print_flag == 1)
                    printf("Line no. %d\t\tLexeme %s\t\tToken %s\n", line_num, lexeme, "TK_CL");
                if(lookup_symbol_table(symbol_table, lexeme) == NULL)
                    insert_lexeme_token(symbol_table, lexeme, TK_CL);
                insert_lexeme_out(lexer_output, lexeme, TK_CL, line_num);
                *beg_pointer = *fwd_pointer;
                beg_buf = fwd_buf;
                state = 0;
                break;

            //accept state for +
            case 7:
                lexeme = get_lexeme(fwd_pointer, beg_pointer, fwd_buf, beg_buf);
                if(print_flag == 1)
                    printf("Line no. %d\t\tLexeme %s\t\tToken %s\n", line_num, lexeme, "TK_PLUS");
                if(lookup_symbol_table(symbol_table, lexeme) == NULL)
                    insert_lexeme_token(symbol_table, lexeme, TK_PLUS);
                insert_lexeme_out(lexer_output, lexeme, TK_PLUS, line_num);
                *beg_pointer = *fwd_pointer;
                beg_buf = fwd_buf;
                state = 0;
                break;

            //accept state for -
            case 8:
                lexeme = get_lexeme(fwd_pointer, beg_pointer, fwd_buf, beg_buf);
                if(print_flag == 1)
                    printf("Line no. %d\t\tLexeme %s\t\tToken %s\n", line_num, lexeme, "TK_MINUS");
                if(lookup_symbol_table(symbol_table, lexeme) == NULL)
                    insert_lexeme_token(symbol_table, lexeme, TK_MINUS);
                insert_lexeme_out(lexer_output, lexeme, TK_MINUS, line_num);
                *beg_pointer = *fwd_pointer;
                beg_buf = fwd_buf;
                state = 0;
                break;

            //accept state for *
            case 9:
                lexeme = get_lexeme(fwd_pointer, beg_pointer, fwd_buf, beg_buf);
                if(print_flag == 1)
                    printf("Line no. %d\t\tLexeme %s\t\tToken %s\n", line_num, lexeme, "TK_MUL");
                if(lookup_symbol_table(symbol_table, lexeme) == NULL)
                    insert_lexeme_token(symbol_table, lexeme, TK_MUL);
                insert_lexeme_out(lexer_output, lexeme, TK_MUL, line_num);
                *beg_pointer = *fwd_pointer;
                beg_buf = fwd_buf;
                state = 0;
                break;

            //accept state for /
            case 10:
                lexeme = get_lexeme(fwd_pointer, beg_pointer, fwd_buf, beg_buf);
                if(print_flag == 1)
                    printf("Line no. %d\t\tLexeme %s\t\tToken %s\n", line_num, lexeme, "TK_DIV");
                if(lookup_symbol_table(symbol_table, lexeme) == NULL)
                    insert_lexeme_token(symbol_table, lexeme, TK_DIV);
                insert_lexeme_out(lexer_output, lexeme, TK_DIV, line_num);
                *beg_pointer = *fwd_pointer;
                beg_buf = fwd_buf;
                state = 0;
                break;

            //accept state for ~
            case 11:
                lexeme = get_lexeme(fwd_pointer, beg_pointer, fwd_buf, beg_buf);
                if(print_flag == 1)
                    printf("Line no. %d\t\tLexeme %s\t\tToken %s\n", line_num, lexeme, "TK_NOT");
                if(lookup_symbol_table(symbol_table, lexeme) == NULL)
                    insert_lexeme_token(symbol_table, lexeme, TK_NOT);
                insert_lexeme_out(lexer_output, lexeme, TK_NOT, line_num);
                *beg_pointer = *fwd_pointer;
                beg_buf = fwd_buf;
                state = 0;
                break;

            // intermediate state for ==
            case 12:
                // Error that occurs due to end of file
                if(*fwd_pointer == *char_read && *char_read < buffer_size / 2)
                {
                    // state 200 defines invalid pattern error
                    state = 200;
                }
                else if(fwd_buf[*fwd_pointer] == '=')
                {
                    state = 13;
                    fwd_buf = increment_pointer(fwd_pointer, buf1, buf2, fwd_buf, char_read, prog_fp, refill_flag);
                }
                else
                {
                    // state 200 defines invalid pattern error
                    state = 200;
                }
                goto begin_switch;
            
            // accept state for ==
            case 13:
                lexeme = get_lexeme(fwd_pointer, beg_pointer, fwd_buf, beg_buf);
                if(print_flag == 1)
                    printf("Line no. %d\t\tLexeme %s\t\tToken %s\n", line_num, lexeme, "TK_EQ");
                if(lookup_symbol_table(symbol_table, lexeme) == NULL)
                    insert_lexeme_token(symbol_table, lexeme, TK_EQ);
                insert_lexeme_out(lexer_output, lexeme, TK_EQ, line_num);
                *beg_pointer = *fwd_pointer;
                beg_buf = fwd_buf;
                state = 0;
                break;

            // Intermediate state for either > or >= 
            case 14:
                // if we reach end of file
                if(*fwd_pointer == *char_read && *char_read < buffer_size / 2)
                {
                    state = 16;
                }
                else if(fwd_buf[*fwd_pointer] == '=')
                {
                    state = 15;
                    fwd_buf = increment_pointer(fwd_pointer, buf1, buf2, fwd_buf, char_read, prog_fp, refill_flag);
                }
                else
                {
                    state = 16;
                }
                goto begin_switch;

            // accept state for >=
            case 15:
                lexeme = get_lexeme(fwd_pointer, beg_pointer, fwd_buf, beg_buf);
                if(print_flag == 1)
                    printf("Line no. %d\t\tLexeme %s\t\tToken %s\n", line_num, lexeme, "TK_GE");
                if(lookup_symbol_table(symbol_table, lexeme) == NULL)
                    insert_lexeme_token(symbol_table, lexeme, TK_GE);
                insert_lexeme_out(lexer_output, lexeme, TK_GE, line_num);
                *beg_pointer = *fwd_pointer;
                beg_buf = fwd_buf;
                state = 0;
                break;

            // accept state for >
            case 16:
                lexeme = get_lexeme(fwd_pointer, beg_pointer, fwd_buf, beg_buf);
                if(print_flag == 1)
                    printf("Line no. %d\t\tLexeme %s\t\tToken %s\n", line_num, lexeme, "TK_GT");
                if(lookup_symbol_table(symbol_table, lexeme) == NULL)
                    insert_lexeme_token(symbol_table, lexeme, TK_GT);
                insert_lexeme_out(lexer_output, lexeme, TK_GT, line_num);
                *beg_pointer = *fwd_pointer;
                beg_buf = fwd_buf;
                state = 0;
                break;

            // intermediate state for !=
            case 17:
                // Error that occurs due to end of file
                if(*fwd_pointer == *char_read && *char_read < buffer_size / 2)
                {
                    // state 200 defines invalid pattern error
                    state = 200;
                }
                else if(fwd_buf[*fwd_pointer] == '=')
                {
                    state = 18;
                    fwd_buf = increment_pointer(fwd_pointer, buf1, buf2, fwd_buf, char_read, prog_fp, refill_flag);
                }
                else
                {
                    // state 200 defines invalid pattern error
                    state = 200;
                }
                goto begin_switch;

            // accept state for !=
            case 18:
                lexeme = get_lexeme(fwd_pointer, beg_pointer, fwd_buf, beg_buf);
                if(print_flag == 1)
                    printf("Line no. %d\t\tLexeme %s\t\tToken %s\n", line_num, lexeme, "TK_NE");
                if(lookup_symbol_table(symbol_table, lexeme) == NULL)
                    insert_lexeme_token(symbol_table, lexeme, TK_NE);
                insert_lexeme_out(lexer_output, lexeme, TK_NE, line_num);
                *beg_pointer = *fwd_pointer;
                beg_buf = fwd_buf;
                state = 0;
                break;

            //accept state for [
            case 19:
                lexeme = get_lexeme(fwd_pointer, beg_pointer, fwd_buf, beg_buf);
                if(print_flag == 1)
                    printf("Line no. %d\t\tLexeme %s\t\tToken %s\n", line_num, lexeme, "TK_SQL");
                if(lookup_symbol_table(symbol_table, lexeme) == NULL)
                    insert_lexeme_token(symbol_table, lexeme, TK_SQL);
                insert_lexeme_out(lexer_output, lexeme, TK_SQL, line_num);
                *beg_pointer = *fwd_pointer;
                beg_buf = fwd_buf;
                state = 0;
                break;

            //accept state for ]
            case 20:
                lexeme = get_lexeme(fwd_pointer, beg_pointer, fwd_buf, beg_buf);
                if(print_flag == 1)
                    printf("Line no. %d\t\tLexeme %s\t\tToken %s\n", line_num, lexeme, "TK_SQR");
                if(lookup_symbol_table(symbol_table, lexeme) == NULL)
                    insert_lexeme_token(symbol_table, lexeme, TK_SQR);
                insert_lexeme_out(lexer_output, lexeme, TK_SQR, line_num);
                *beg_pointer = *fwd_pointer;
                beg_buf = fwd_buf;
                state = 0;
                break;

            // state for comment
            case 21:
                // if we reach end of file
                if(*fwd_pointer == *char_read && *char_read < buffer_size / 2)
                {
                    state = 58;
                    flag = 1;
                }
                else if(fwd_buf[*fwd_pointer] != '\n')
                {
                    state = 21;
                    fwd_buf = increment_pointer(fwd_pointer, buf1, buf2, fwd_buf, char_read, prog_fp, refill_flag);
                }
                else
                {
                    state = 58;
                    flag = 1;
                    fwd_buf = increment_pointer(fwd_pointer, buf1, buf2, fwd_buf, char_read, prog_fp, refill_flag);
                }
                goto begin_switch;


            // intermediate state 1 for &&&
            case 22:
                // Error that occurs due to end of file
                if(*fwd_pointer == *char_read && *char_read < buffer_size / 2)
                {
                    // state 200 defines invalid pattern error
                    state = 200;
                }
                else if(fwd_buf[*fwd_pointer] == '&')
                {
                    state = 23;
                    fwd_buf = increment_pointer(fwd_pointer, buf1, buf2, fwd_buf, char_read, prog_fp, refill_flag);
                }
                else
                {
                    // state 200 defines invalid pattern error
                    state = 200;
                }
                goto begin_switch;

            // intermediate state 2 for &&& 
            case 23:
                // Error that occurs due to end of file
                if(*fwd_pointer == *char_read && *char_read < buffer_size / 2)
                {
                    // state 200 defines invalid pattern error
                    state = 200;
                }
                else if(fwd_buf[*fwd_pointer] == '&')
                {
                    state = 24;
                    fwd_buf = increment_pointer(fwd_pointer, buf1, buf2, fwd_buf, char_read, prog_fp, refill_flag);
                }
                else
                {
                    // state 200 defines invalid pattern error
                    state = 200;
                }
                goto begin_switch;

            // accept state for &&&
            case 24:
                lexeme = get_lexeme(fwd_pointer, beg_pointer, fwd_buf, beg_buf);
                if(print_flag == 1)
                    printf("Line no. %d\t\tLexeme %s\t\tToken %s\n", line_num, lexeme, "TK_AND");
                if(lookup_symbol_table(symbol_table, lexeme) == NULL)
                    insert_lexeme_token(symbol_table, lexeme, TK_AND);
                insert_lexeme_out(lexer_output, lexeme, TK_AND, line_num);
                *beg_pointer = *fwd_pointer;
                beg_buf = fwd_buf;
                state = 0;
                break;

            // intermediate state 1 for &&&
            case 25:
                // Error that occurs due to end of file
                if(*fwd_pointer == *char_read && *char_read < buffer_size / 2)
                {
                    // state 200 defines invalid pattern error
                    state = 200;
                }
                else if(fwd_buf[*fwd_pointer] == '@')
                {
                    state = 26;
                    fwd_buf = increment_pointer(fwd_pointer, buf1, buf2, fwd_buf, char_read, prog_fp, refill_flag);
                }
                else
                {
                    // state 200 defines invalid pattern error
                    state = 200;
                }
                goto begin_switch;

            // intermediate state 2 for @@@
            case 26:
                // Error that occurs due to end of file
                if(*fwd_pointer == *char_read && *char_read < buffer_size / 2)
                {
                    // state 200 defines invalid pattern error
                    state = 200;
                }
                else if(fwd_buf[*fwd_pointer] == '@')
                {
                    state = 27;
                    fwd_buf = increment_pointer(fwd_pointer, buf1, buf2, fwd_buf, char_read, prog_fp, refill_flag);
                }
                else
                {
                    // state 200 defines invalid pattern error
                    state = 200;
                }
                goto begin_switch;

            // accept state for @@@
            case 27:
                lexeme = get_lexeme(fwd_pointer, beg_pointer, fwd_buf, beg_buf);
                if(print_flag == 1)
                    printf("Line no. %d\t\tLexeme %s\t\tToken %s\n", line_num, lexeme, "TK_OR");
                if(lookup_symbol_table(symbol_table, lexeme) == NULL)
                    insert_lexeme_token(symbol_table, lexeme, TK_OR);
                insert_lexeme_out(lexer_output, lexeme, TK_OR, line_num);
                *beg_pointer = *fwd_pointer;
                beg_buf = fwd_buf;
                state = 0;
                break;

            // intermediate state for < or <= or  <---
            case 28:
                // if we reach end of file
                if(*fwd_pointer == *char_read && *char_read < buffer_size / 2)
                {
                    state = 33;
                }
                else if(fwd_buf[*fwd_pointer] == '-')
                {
                    state = 29;
                    fwd_buf = increment_pointer(fwd_pointer, buf1, buf2, fwd_buf, char_read, prog_fp, refill_flag);
                }
                else if(fwd_buf[*fwd_pointer] == '=')
                {
                    state = 32;
                    fwd_buf = increment_pointer(fwd_pointer, buf1, buf2, fwd_buf, char_read, prog_fp, refill_flag);
                }
                else
                {
                    state = 33;
                }
                goto begin_switch;

            // intermediate state 1 for <--- 
            case 29:
                // if we reach  end of file
                if(*fwd_pointer == *char_read && *char_read < buffer_size / 2)
                {
                    state = 33;
                    fwd_buf = decrement_pointer(fwd_pointer, buf1, buf2, fwd_buf, refill_flag);
                }
                else if(fwd_buf[*fwd_pointer] == '-')
                {
                    state = 30;
                    fwd_buf = increment_pointer(fwd_pointer, buf1, buf2, fwd_buf, char_read, prog_fp, refill_flag);
                }
                else
                {
                    state = 33;
                    fwd_buf = decrement_pointer(fwd_pointer,buf1, buf2, fwd_buf, refill_flag);
                }
                goto begin_switch;

            // intermediate state 2 for <--- 
            case 30:
                // Error that occurs due to end of file
                if(*fwd_pointer == *char_read && *char_read < buffer_size / 2)
                {
                    // state 200 defines invalid pattern error
                    state = 200;
                }
                else if(fwd_buf[*fwd_pointer] == '-')
                {
                    state = 31;
                    fwd_buf = increment_pointer(fwd_pointer, buf1, buf2, fwd_buf, char_read, prog_fp, refill_flag);
                }
                else
                {
                    // state 200 defines invalid pattern error
                    state = 200;
                }
                goto begin_switch;

            // accept state for <---
            case 31:
                lexeme = get_lexeme(fwd_pointer, beg_pointer, fwd_buf, beg_buf);
                if(print_flag == 1)
                    printf("Line no. %d\t\tLexeme %s\t\tToken %s\n", line_num, lexeme, "TK_ASSIGNOP");
                if(lookup_symbol_table(symbol_table, lexeme) == NULL)
                    insert_lexeme_token(symbol_table, lexeme, TK_ASSIGNOP);
                insert_lexeme_out(lexer_output, lexeme, TK_ASSIGNOP, line_num);
                *beg_pointer = *fwd_pointer;
                beg_buf = fwd_buf;
                state = 0;
                break;

            // accept state for <=
            case 32:
                lexeme = get_lexeme(fwd_pointer, beg_pointer, fwd_buf, beg_buf);
                if(print_flag == 1)
                    printf("Line no. %d\t\tLexeme %s\t\tToken %s\n", line_num, lexeme, "TK_LE");
                if(lookup_symbol_table(symbol_table, lexeme) == NULL)
                    insert_lexeme_token(symbol_table, lexeme, TK_LE);
                insert_lexeme_out(lexer_output, lexeme, TK_LE, line_num);
                *beg_pointer = *fwd_pointer;
                beg_buf = fwd_buf;
                state = 0;
                break;
            
            // accept state for <
            case 33:
                lexeme = get_lexeme(fwd_pointer, beg_pointer, fwd_buf, beg_buf);
                if(print_flag == 1)
                    printf("Line no. %d\t\tLexeme %s\t\tToken %s\n", line_num, lexeme, "TK_LT");
                if(lookup_symbol_table(symbol_table, lexeme) == NULL)
                    insert_lexeme_token(symbol_table, lexeme, TK_LT);
                insert_lexeme_out(lexer_output, lexeme, TK_LT, line_num);
                *beg_pointer = *fwd_pointer;
                beg_buf = fwd_buf;
                state = 0;
                break;

            // intermediate state for int or real
            case 34:
                // if we reach end of file
                if(*fwd_pointer == *char_read && *char_read < buffer_size / 2)
                {
                    state = 36;
                }
                else if(fwd_buf[*fwd_pointer] >= '0' && fwd_buf[*fwd_pointer] <= '9')
                {
                    state = 34;
                    fwd_buf = increment_pointer(fwd_pointer, buf1, buf2, fwd_buf, char_read, prog_fp, refill_flag);
                }
                else if(fwd_buf[*fwd_pointer] == '.')
                {
                    state = 35;
                    fwd_buf = increment_pointer(fwd_pointer, buf1, buf2, fwd_buf, char_read, prog_fp, refill_flag);
                }
                else
                {
                    state = 36;
                }
                goto begin_switch;

            // intermediate state 1 for real 
            case 35:
                // if we reach end of file
                if(*fwd_pointer == *char_read && *char_read < buffer_size / 2)
                {
                    state = 36;
                    fwd_buf = decrement_pointer(fwd_pointer,buf1, buf2, fwd_buf, refill_flag);
                }
                else if(fwd_buf[*fwd_pointer] >= '0' && fwd_buf[*fwd_pointer] <= '9')
                {
                    state = 37;
                    fwd_buf = increment_pointer(fwd_pointer, buf1, buf2, fwd_buf, char_read, prog_fp, refill_flag);
                }
                else
                {
                    state = 36;
                    fwd_buf = decrement_pointer(fwd_pointer,buf1, buf2, fwd_buf, refill_flag);
                }
                goto begin_switch;

            // accept state for int
            case 36:
                lexeme = get_lexeme(fwd_pointer, beg_pointer, fwd_buf, beg_buf);
                if(print_flag == 1)
                    printf("Line no. %d\t\tLexeme %s\t\tToken %s\n", line_num, lexeme, "TK_NUM");
                if(lookup_symbol_table(symbol_table, lexeme) == NULL)
                    insert_lexeme_token(symbol_table, lexeme, TK_NUM);
                insert_lexeme_out(lexer_output, lexeme, TK_NUM, line_num);
                *beg_pointer = *fwd_pointer;
                beg_buf = fwd_buf;
                state = 0;
                break;

            // intermediate state 2 for real 
            case 37:
                // Error that occurs due to end of file
                if(*fwd_pointer == *char_read && *char_read < buffer_size / 2)
                {
                    // state 200 defines invalid pattern error
                    state = 200;
                }
                else if(fwd_buf[*fwd_pointer] >= '0' && fwd_buf[*fwd_pointer] <= '9')
                {
                    state = 38;
                    fwd_buf = increment_pointer(fwd_pointer, buf1, buf2, fwd_buf, char_read, prog_fp, refill_flag);
                }
                else
                {
                    // state 200 defines invalid pattern error
                    state = 200;
                }
                goto begin_switch;    

            // intermediate state 3 for real
            case 38:
                // if we reach end of file
                if(*fwd_pointer == *char_read && *char_read < buffer_size / 2)
                {
                    state = 42;
                }
                else if(fwd_buf[*fwd_pointer] == 'E')
                {
                    state = 39;
                    fwd_buf = increment_pointer(fwd_pointer, buf1, buf2, fwd_buf, char_read, prog_fp, refill_flag);
                }
                else
                {
                    state = 42;
                }
                goto begin_switch;
            
            // intermediate state 4 for real 
            case 39:
                // Error that occurs due to end of file
                if(*fwd_pointer == *char_read && *char_read < buffer_size / 2)
                {
                    // state 200 defines invalid pattern error
                    state = 200;
                }
                else if(fwd_buf[*fwd_pointer] >= '0' && fwd_buf[*fwd_pointer] <= '9')
                {
                    state = 41;
                    fwd_buf = increment_pointer(fwd_pointer, buf1, buf2, fwd_buf, char_read, prog_fp, refill_flag);
                }
                else if(fwd_buf[*fwd_pointer] == '-' || fwd_buf[*fwd_pointer] == '+')
                {
                    state = 40;
                    fwd_buf = increment_pointer(fwd_pointer, buf1, buf2, fwd_buf, char_read, prog_fp, refill_flag);
                }
                else
                {
                    // state 200 defines invalid pattern error
                    state = 200;
                }
                goto begin_switch;   

            // intermediate state 5 for real 
            case 40:
                // Error that occurs due to end of file
                if(*fwd_pointer == *char_read && *char_read < buffer_size / 2)
                {
                    // state 200 defines invalid pattern error
                    state = 200;
                }
                else if(fwd_buf[*fwd_pointer] >= '0' && fwd_buf[*fwd_pointer] <= '9')
                {
                    state = 41;
                    fwd_buf = increment_pointer(fwd_pointer, buf1, buf2, fwd_buf, char_read, prog_fp, refill_flag);
                }
                else
                {
                    // state 200 defines invalid pattern error
                    state = 200;
                }
                goto begin_switch;   

            // intermediate state 6 for real 
            case 41:
                // Error that occurs due to end of file
                if(*fwd_pointer == *char_read && *char_read < buffer_size / 2)
                {
                    // state 200 defines invalid pattern error
                    state = 200;
                }
                else if(fwd_buf[*fwd_pointer] >= '0' && fwd_buf[*fwd_pointer] <= '9')
                {
                    state = 42;
                    fwd_buf = increment_pointer(fwd_pointer, buf1, buf2, fwd_buf, char_read, prog_fp, refill_flag);
                }
                else
                {
                    // state 200 defines invalid pattern error
                    state = 200;
                }
                goto begin_switch;  

            // accept state for real
            case 42:
                lexeme = get_lexeme(fwd_pointer, beg_pointer, fwd_buf, beg_buf);
                if(print_flag == 1)
                    printf("Line no. %d\t\tLexeme %s\t\tToken %s\n", line_num, lexeme, "TK_RNUM");
                if(lookup_symbol_table(symbol_table, lexeme) == NULL)
                    insert_lexeme_token(symbol_table, lexeme, TK_RNUM);
                insert_lexeme_out(lexer_output, lexeme, TK_RNUM, line_num);
                *beg_pointer = *fwd_pointer;
                beg_buf = fwd_buf;
                state = 0;
                break; 

            // Intermediate state 1 for RUID
            case 43:
                // Error that occurs due to end of file
                if(*fwd_pointer == *char_read && *char_read < buffer_size / 2)
                {
                    // state 200 defines invalid pattern error
                    state = 200;
                }
                else if(fwd_buf[*fwd_pointer] >= 'a' && fwd_buf[*fwd_pointer] <= 'z')
                {
                    state = 44;
                    fwd_buf = increment_pointer(fwd_pointer, buf1, buf2, fwd_buf, char_read, prog_fp, refill_flag);
                }
                else
                {
                    // state 200 defines invalid pattern error
                    state = 200;
                }
                goto begin_switch; 

            // Intermediate state 2 for RUID
            case 44:
                //if we reach end of file
                if(*fwd_pointer == *char_read && *char_read < buffer_size / 2)
                {
                    state = 45;
                }
                else if(fwd_buf[*fwd_pointer] >= 'a' && fwd_buf[*fwd_pointer] <= 'z')
                {
                    state = 44;
                    fwd_buf = increment_pointer(fwd_pointer, buf1, buf2, fwd_buf, char_read, prog_fp, refill_flag);
                }
                else
                {
                    state = 45;
                }
                goto begin_switch; 

            // accept state for RUID
            case 45:
                lexeme = get_lexeme(fwd_pointer, beg_pointer, fwd_buf, beg_buf);
                if(print_flag == 1)
                    printf("Line no. %d\t\tLexeme %s\t\tToken %s\n", line_num, lexeme, "TK_RUID");
                if(lookup_symbol_table(symbol_table, lexeme) == NULL)
                    insert_lexeme_token(symbol_table, lexeme, TK_RUID);
                insert_lexeme_out(lexer_output, lexeme, TK_RUID, line_num);
                *beg_pointer = *fwd_pointer;
                beg_buf = fwd_buf;
                state = 0;
                break;  

            // Intermediate state 1 for _main or funid
            case 46:
                // Error that occurs due to end of file
                if(*fwd_pointer == *char_read && *char_read < buffer_size / 2)
                {
                    // state 200 defines invalid pattern error
                    state = 200;
                }
                else if((fwd_buf[*fwd_pointer] >= 'a' && fwd_buf[*fwd_pointer] <= 'z')|| (fwd_buf[*fwd_pointer] >= 'A' && fwd_buf[*fwd_pointer] <= 'Z'))
                {
                    state = 47;
                    fwd_buf = increment_pointer(fwd_pointer, buf1, buf2, fwd_buf, char_read, prog_fp, refill_flag);
                }
                else
                {
                    // state 200 defines invalid pattern error
                    state = 200;
                }
                goto begin_switch; 
            
            // Intermediate state 2 for _main or funid
            case 47:
                // if we reach end of file
                if(*fwd_pointer == *char_read && *char_read < buffer_size / 2)
                {
                    state = 49;
                }
                else if((fwd_buf[*fwd_pointer] >= 'a' && fwd_buf[*fwd_pointer] <= 'z')|| (fwd_buf[*fwd_pointer] >= 'A' && fwd_buf[*fwd_pointer] <= 'Z'))
                {
                    state = 47;
                    fwd_buf = increment_pointer(fwd_pointer, buf1, buf2, fwd_buf, char_read, prog_fp, refill_flag);
                }
                else if(fwd_buf[*fwd_pointer] >= '0' && fwd_buf[*fwd_pointer] <= '9')
                {
                    state = 48;
                    fwd_buf = increment_pointer(fwd_pointer, buf1, buf2, fwd_buf, char_read, prog_fp, refill_flag);
                }
                else 
                {
                    state = 49;
                }
                goto begin_switch; 

            // Intermediate state 3 for  funid
            case 48:
                // if we reach end of file
                if(*fwd_pointer == *char_read && *char_read < buffer_size / 2)
                {
                    state = 49;
                }
                else if(fwd_buf[*fwd_pointer] >= '0' && fwd_buf[*fwd_pointer] <= '9')
                {
                    state = 48;
                    fwd_buf = increment_pointer(fwd_pointer, buf1, buf2, fwd_buf, char_read, prog_fp, refill_flag);
                }
                else 
                {
                    state = 49;
                }
                goto begin_switch; 

            // accept state for _main or funid
            case 49:
                lexeme = get_lexeme(fwd_pointer, beg_pointer, fwd_buf, beg_buf);

                // check if funid is of appropiate length or not
                if(strlen(lexeme) > 30)
                {
                    state = 201;
                    goto begin_switch;
                }
                else
                {
                    SYM_ROW temp = lookup_symbol_table(symbol_table, lexeme);
                    if( temp == NULL)
                    {
                        insert_lexeme_token(symbol_table, lexeme, TK_FUNID);
                        if(print_flag == 1)
                            printf("Line no. %d\t\tLexeme %s\t\tToken %s\n", line_num, lexeme, "TK_FUNID");
                        insert_lexeme_out(lexer_output, lexeme, TK_FUNID, line_num);
                    }
                    else
                    {
                        if(print_flag == 1)
                            printf("Line no. %d\t\tLexeme %s\t\tToken %s\n", line_num, lexeme, token_to_string[temp -> token]);
                        insert_lexeme_out(lexer_output, lexeme, temp -> token , line_num);
                    }
                }
                *beg_pointer = *fwd_pointer;
                beg_buf = fwd_buf;
                state = 0;
                break;   

            // Intermediate state 1 for either field ID or ID
            case 50:
                // if we reach end of file
                if(*fwd_pointer == *char_read && *char_read < buffer_size / 2)
                {
                    state = 52;
                }
                else if((fwd_buf[*fwd_pointer] >= 'a' && fwd_buf[*fwd_pointer] <= 'z'))
                {
                    state = 51;
                    fwd_buf = increment_pointer(fwd_pointer, buf1, buf2, fwd_buf, char_read, prog_fp, refill_flag);
                }
                else if(fwd_buf[*fwd_pointer] >= '2' && fwd_buf[*fwd_pointer] <= '7')
                {
                    state = 53;
                    fwd_buf = increment_pointer(fwd_pointer, buf1, buf2, fwd_buf, char_read, prog_fp, refill_flag);
                }
                else 
                {
                    state = 52;
                }
                goto begin_switch; 

            // Intermediate state 2 for field ID
            case 51:
                // if we reach end of file
                if(*fwd_pointer == *char_read && *char_read < buffer_size / 2)
                {
                    state = 52;
                }
                else if((fwd_buf[*fwd_pointer] >= 'a' && fwd_buf[*fwd_pointer] <= 'z'))
                {
                    state = 51;
                    fwd_buf = increment_pointer(fwd_pointer, buf1, buf2, fwd_buf, char_read, prog_fp, refill_flag);
                }
                else 
                {
                    state = 52;
                }
                goto begin_switch; 

            // accept state for FIELDID
            case 52:
                lexeme = get_lexeme(fwd_pointer, beg_pointer, fwd_buf, beg_buf);
                SYM_ROW temp = lookup_symbol_table(symbol_table, lexeme);
                if( temp == NULL)
                {
                    insert_lexeme_token(symbol_table, lexeme, TK_FIELDID);
                    if(print_flag == 1)
                        printf("Line no. %d\t\tLexeme %s\t\tToken %s\n", line_num, lexeme, "TK_FIELDID");
                    insert_lexeme_out(lexer_output, lexeme, TK_FIELDID, line_num);
                }
                else
                {
                    if(print_flag == 1)
                        printf("Line no. %d\t\tLexeme %s\t\tToken %s\n", line_num, lexeme, token_to_string[temp -> token]);
                    insert_lexeme_out(lexer_output, lexeme, temp -> token, line_num);
                }
                    
                *beg_pointer = *fwd_pointer;
                beg_buf = fwd_buf;
                state = 0;
                break;  
            
            // Intermediate state 2 for ID
            case 53:
                // if we reach end of file
                if(*fwd_pointer == *char_read && *char_read < buffer_size / 2)
                {
                    state = 55;
                }
                else if((fwd_buf[*fwd_pointer] >= 'b' && fwd_buf[*fwd_pointer] <= 'd'))
                {
                    state = 53;
                    fwd_buf = increment_pointer(fwd_pointer, buf1, buf2, fwd_buf, char_read, prog_fp, refill_flag);
                }
                else if(fwd_buf[*fwd_pointer] >= '2' && fwd_buf[*fwd_pointer] <= '7')
                {
                    state = 54;
                    fwd_buf = increment_pointer(fwd_pointer, buf1, buf2, fwd_buf, char_read, prog_fp, refill_flag);
                }
                else 
                {
                    state = 55;
                }
                goto begin_switch; 


            // Intermediate state 3 for ID
            case 54:
                // if we reach end of file
                if(*fwd_pointer == *char_read && *char_read < buffer_size / 2)
                {
                    state = 55;
                }
                else if(fwd_buf[*fwd_pointer] >= '2' && fwd_buf[*fwd_pointer] <= '7')
                {
                    state = 54;
                    fwd_buf = increment_pointer(fwd_pointer, buf1, buf2, fwd_buf, char_read, prog_fp, refill_flag);
                }
                else 
                {
                    state = 55;
                }
                goto begin_switch; 

            // accept state for ID
            case 55:
                lexeme = get_lexeme(fwd_pointer, beg_pointer, fwd_buf, beg_buf);
                // check if id is of correct size
                if(strlen(lexeme) > 20)
                {
                    state = 202;
                    goto begin_switch;
                }
                if(print_flag == 1)
                    printf("Line no. %d\t\tLexeme %s\t\tToken %s\n", line_num, lexeme, "TK_ID");
                if(lookup_symbol_table(symbol_table, lexeme) == NULL)
                    insert_lexeme_token(symbol_table, lexeme, TK_ID);
                insert_lexeme_out(lexer_output, lexeme, TK_ID, line_num);
                *beg_pointer = *fwd_pointer;
                beg_buf = fwd_buf;
                state = 0;
                break;  

            // accept state for tab character
            case 56:
                //printf("\t");
                *beg_pointer = *fwd_pointer;
                beg_buf = fwd_buf;
                state = 0;
                break;

            // accept state for space character
            case 57:
                //printf(" ");
                *beg_pointer = *fwd_pointer;
                beg_buf = fwd_buf;
                state = 0;
                break;

            // accept state for new line character or comment 
            case 58:
                if(flag == 1)
                {
                    lexeme = (char*)calloc(2, sizeof(char));
                    *lexeme = '%'; 
                    *(lexeme + 1) = '\0';
                    if(print_flag == 1)
                        printf("Line no. %d\t\tLexeme %s\t\tToken %s\n", line_num, lexeme, "TK_COMMENT");
                    if(lookup_symbol_table(symbol_table, lexeme) == NULL)
                        insert_lexeme_token(symbol_table, lexeme, TK_COMMENT);
                    flag = 0;
                }
                //printf("\n");
                line_num++;
                *beg_pointer = *fwd_pointer;
                beg_buf = fwd_buf;
                state = 0;
                break;

            
            // Incorrect pattern error state.
            case 200:
                lexeme = get_lexeme(fwd_pointer, beg_pointer, fwd_buf, beg_buf);
                if(print_flag == 1)
                    printf("Line no. %d : Error: Unknown pattern <%s>\n", line_num, lexeme);
                insert_lexeme_out(lexer_output, lexeme, TK_ERROR1, line_num);
                *beg_pointer = *fwd_pointer;
                beg_buf = fwd_buf;
                state = 0;
                break;

            // Function id exceeding length error
            case 201:
                if(print_flag == 1)
                    printf("Line no. %d : Error: Funtion identifier is longer than the prescribed length of 30 chararcters.\n", line_num);
                insert_lexeme_out(lexer_output, "", TK_ERROR2, line_num);
                *beg_pointer = *fwd_pointer;
                beg_buf = fwd_buf;
                state = 0;
                break;

            //  id exceeding length error
            case 202:
                if(print_flag == 1)
                    printf("Line no. %d : Error: Variable identifier is longer than the prescribed length of 20 chararcters.\n", line_num);
                insert_lexeme_out(lexer_output, "", TK_ERROR3, line_num);
                *beg_pointer = *fwd_pointer;
                beg_buf = fwd_buf;
                state = 0;
                break;

            // illegal character error
            case 203:
                lexeme = get_lexeme(fwd_pointer, beg_pointer, fwd_buf, beg_buf);
                if(print_flag == 1)
                    printf("Line no. %d : Error: Unknown symbol <%s>\n", line_num, lexeme);
                insert_lexeme_out(lexer_output, lexeme, TK_ERROR4, line_num);
                *beg_pointer = *fwd_pointer;
                beg_buf = fwd_buf;
                state = 0;
                break;

            
            default:
                printf("No state with number: %d\n", state);
        }

        // condition if we reach end of file
        if(*fwd_pointer == *char_read && *char_read < buffer_size / 2)
        {
            //printf("\n\nReached End Of File\n\n");
            break;
        }
    }

    // display the contents of symbol table
    //printf("Displaying Symbol table \n\n");
    //display_symbol_table(symbol_table, token_to_string);

    // display the contents of lexer output
    //printf("\n\nDisplaying lexer output \n\n");
    //display_lexer_output(lexer_output, token_to_string);


    // deallocate memory.
    destroy_symbol_table(symbol_table);
    free(buf1);
    free(buf2);
    free(fwd_pointer);
    free(beg_pointer);
    free(char_read);

    return lexer_output;
}