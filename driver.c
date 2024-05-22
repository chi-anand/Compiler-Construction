// Group No. : 13
// Adarsh Goel 2020B3A70821P
// Chinmay Anand 2020B3A70800P
// Arjoo Kumari 2020B3A70770P
// Mehak Agarwal 2020B3A70868P
// Jay Prakash Mundhra 2020B3A70799P

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "global.h"
#include "hashMap.h"
#include "parser.h"
#include "tree.h"
#include <time.h>
void remove_comments(FILE* prog_fp)
{
    // define line read variable
    char* line;
    line = (char *) malloc(sizeof(char) * 256);


    // read the grammar.txt line by line
    while(fgets(line, sizeof(char) * 256, prog_fp))
    {
        for(int i = 0; i < strlen(line); ++i)
        {
            if(line[i] == '%')
            {
                printf("\n");
                break;
            }
            printf("%c", line[i]);
        }
       
    }
}
int main(int argc, char* argv[])
{
    clock_t start_time, end_time;
    double total_CPU_time, total_CPU_time_in_seconds;

    // initialise global variable
    char** token_to_string = build_token_to_string();
    HASHMAP string_to_token = build_string_to_token_map(token_to_string);

    printf("1. Both Lexer and Parser module implemented\n");
    printf("2. First and Follow set automated\n");
    printf("3. Modules works with all the test cases\n");

    printf("\n----------------------------------------------------------------\n\n");
    while(1)
    {
        int state;
        printf("Enter 0 to exit \n");
        printf("Enter 1 for removal of comments \n");
        printf("Enter 2 to print token list by lexer \n");
        printf("Enter 3 to print parse tree \n");
        printf("Enter 4 to print time taken by lexer and parser\n");
        printf("Enter your choice : ");
        scanf("%d", &state);
        printf("\n\n");
        if(state == 0)
            break;
        else if(state == 1)
        {
            // opening program file
            FILE* prog_fp = fopen(argv[1], "r");
            if(!prog_fp)
            {
                printf("Error opening file \n");
                exit(0);
            }
            remove_comments(prog_fp);
            printf("\n");
            printf("--------------------------------------------------------------------------------\n\n");
            fclose(prog_fp);

        }
        else if(state == 2)
        {
            // opening program file
            FILE* prog_fp = fopen(argv[1], "r");
            while(!prog_fp)
            {
                printf("Error opening file \n");
                exit(0);
            }
            LEX_OUT lexer_output = compute_tokens(token_to_string, 1, prog_fp);
            //destroy_lex_out(lexer_output);
            printf("\n");
            printf("--------------------------------------------------------------------------------\n\n");
            fclose(prog_fp);
        }
        else if(state == 3)
        {
            // opening program file
            start_time = clock();
            FILE* prog_fp = fopen(argv[1], "r");
            if(!prog_fp)
            {
                printf("Error opening file \n");
                exit(0);
            }
            FILE* parse_fp = fopen(argv[2], "w");
             if(!parse_fp)
            {
                printf("Error opening file \n");
                exit(0);
            }
            lexer_and_parser(token_to_string, string_to_token, prog_fp, parse_fp);
            fclose(prog_fp);
            fclose(parse_fp);
            end_time = clock();

            printf("\n");
            printf("--------------------------------------------------------------------------------\n\n");

        }
        else if(state == 4)
        {
            total_CPU_time = (double) (end_time - start_time);
            total_CPU_time_in_seconds = total_CPU_time / CLOCKS_PER_SEC;
            printf("Total CPU Time : %f \n", total_CPU_time);
            printf("Total CPU Time in seconds : %f \n", total_CPU_time_in_seconds);
            printf("\n");
            printf("--------------------------------------------------------------------------------\n\n");
        }
    }
    deleteMap(string_to_token);
    free(token_to_string);
}