#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "lexer.h"

typedef enum{
    INT_LIT,
    STATEMENT,
    SEP,
    BEGIN,
}NodeType;


typedef struct Node{
    char *value;
    NodeType type; 
   struct  Node *right;
   struct Node *left;
}Node;

Token *parser(Token *tokens);

#endif // PARSER_H
