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
#include "global.h"
#include "hashMap.h"

// Function to initialise global variable
char** build_token_to_string()
{
    char** token_to_string =(char **) malloc(sizeof(char *) * NO_OF_TERMINALS);
    token_to_string[0] = "$";
    token_to_string[1] = "TK_ASSIGNOP";
    token_to_string[2] = "TK_COMMENT";
    token_to_string[3] = "TK_FIELDID";
    token_to_string[4] = "TK_ID";
    token_to_string[5] = "TK_NUM";
    token_to_string[6] = "TK_RNUM";
    token_to_string[7] = "TK_FUNID";
    token_to_string[8] = "TK_RUID";
    token_to_string[9] = "TK_WITH";
    token_to_string[10] = "TK_PARAMETERS";
    token_to_string[11] = "TK_END";
    token_to_string[12] = "TK_WHILE";
    token_to_string[13] = "TK_UNION";
    token_to_string[14] = "TK_ENDUNION";
    token_to_string[15] = "TK_DEFINETYPE";
    token_to_string[16] = "TK_AS";
    token_to_string[17] = "TK_TYPE";
    token_to_string[18] = "TK_MAIN";
    token_to_string[19] = "TK_GLOBAL";
    token_to_string[20] = "TK_PARAMETER";
    token_to_string[21] = "TK_LIST";
    token_to_string[22] = "TK_SQL";
    token_to_string[23] = "TK_SQR";
    token_to_string[24] = "TK_INPUT";
    token_to_string[25] = "TK_OUTPUT";
    token_to_string[26] = "TK_INT";
    token_to_string[27] = "TK_REAL";
    token_to_string[28] = "TK_COMMA";
    token_to_string[29] = "TK_SEM";
    token_to_string[30] = "TK_COLON";
    token_to_string[31] = "TK_DOT";
    token_to_string[32] = "TK_ENDWHILE";
    token_to_string[33] = "TK_OP";
    token_to_string[34] = "TK_CL";
    token_to_string[35] = "TK_IF";
    token_to_string[36] = "TK_THEN";
    token_to_string[37] = "TK_ENDIF";
    token_to_string[38] = "TK_READ";
    token_to_string[39] = "TK_WRITE";
    token_to_string[40] = "TK_RETURN";
    token_to_string[41] = "TK_PLUS";
    token_to_string[42] = "TK_MINUS";
    token_to_string[43] = "TK_MUL";
    token_to_string[44] = "TK_DIV";
    token_to_string[45] = "TK_CALL";
    token_to_string[46] = "TK_RECORD";
    token_to_string[47] = "TK_ENDRECORD";
    token_to_string[48] = "TK_ELSE";
    token_to_string[49] = "TK_AND";
    token_to_string[50] = "TK_OR";
    token_to_string[51] = "TK_NOT";
    token_to_string[52] = "TK_LT";
    token_to_string[53] = "TK_LE";
    token_to_string[54] = "TK_EQ";
    token_to_string[55] = "TK_GT";
    token_to_string[56] = "TK_GE";
    token_to_string[57] = "TK_NE";
    return token_to_string;
}

HASHMAP build_string_to_token_map(char** token_to_string)
{
    HASHMAP string_to_token = (HASHMAP) malloc(sizeof(struct hashMap));
    initializeHashMap(string_to_token);
    for(int i = 0; i < NO_OF_TERMINALS; ++i)
        insert(string_to_token, token_to_string[i], i);

    return string_to_token;
}