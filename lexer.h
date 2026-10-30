#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>

#define TO_STRING_HELPER(x) #x
#define TO_STRING(x) TO_STRING_HELPER(x)

typedef enum {
    BEGINNING,
    INT,
    KEYWORD,
    SEPARATOR,
    OPERATOR,
    IDENTIFIER,
    END_OF_TOKENS,
}TokenType;

typedef struct {
    TokenType type;
    /* union{
        // char *s,
        // int val;

    }value*/ 
    char *value;

}Token;

void print_token(Token token);
Token *generate_number(char *,int*);
Token *generate_keyword_or_identifier(char*,int*);
Token *generate_separator_or_operator(char*,int*,TokenType);
Token *lexer(FILE*);

#endif // LEXER_H
