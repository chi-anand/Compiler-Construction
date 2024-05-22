// Group No. : 13
// Adarsh Goel 2020B3A70821P
// Chinmay Anand 2020B3A70800P
// Arjoo Kumari 2020B3A70770P
// Mehak Agarwal 2020B3A70868P
// Jay Prakash Mundhra 2020B3A70799P
#ifndef GLOBAL_H
#define GLOBAL_H
#include "hashMap.h"

#define TK_ASSIGNOP 1
#define TK_COMMENT 2
#define TK_FIELDID 3
#define TK_ID 4
#define TK_NUM 5
#define TK_RNUM 6
#define TK_FUNID 7
#define TK_RUID 8
#define TK_WITH 9
#define TK_PARAMETERS 10
#define TK_END 11
#define TK_WHILE 12
#define TK_UNION 13
#define TK_ENDUNION 14
#define TK_DEFINETYPE 15
#define TK_AS 16
#define TK_TYPE 17
#define TK_MAIN 18
#define TK_GLOBAL 19
#define TK_PARAMETER 20
#define TK_LIST 21
#define TK_SQL 22
#define TK_SQR 23
#define TK_INPUT 24
#define TK_OUTPUT 25
#define TK_INT 26
#define TK_REAL 27
#define TK_COMMA 28
#define TK_SEM 29
#define TK_COLON 30
#define TK_DOT 31
#define TK_ENDWHILE 32
#define TK_OP 33
#define TK_CL 34
#define TK_IF 35
#define TK_THEN 36
#define TK_ENDIF 37
#define TK_READ 38
#define TK_WRITE 39
#define TK_RETURN 40
#define TK_PLUS 41
#define TK_MINUS 42
#define TK_MUL 43
#define TK_DIV 44
#define TK_CALL 45
#define TK_RECORD 46
#define TK_ENDRECORD 47
#define TK_ELSE 48
#define TK_AND 49
#define TK_OR 50
#define TK_NOT 51
#define TK_LT 52
#define TK_LE 53
#define TK_EQ 54
#define TK_GT 55
#define TK_GE 56
#define TK_NE 57
#define TK_EPS 58
#define TK_ERROR1 200
#define TK_ERROR2 201
#define TK_ERROR3 202
#define TK_ERROR4 203
#define NO_OF_TERMINALS 58

char** build_token_to_string();
HASHMAP build_string_to_token_map(char** token_to_string);

#endif