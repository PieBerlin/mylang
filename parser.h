#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "lexer.h"



typedef struct Node{
    char *value;
    TokenType type; 
   struct  Node *right;
   struct Node *left;
}Node;

Node *parser(Token *tokens);
void print_tree(Node*,int,char *);
Node *init_node(char*,TokenType);
void print_error(char*);

#endif // PARSER_H
