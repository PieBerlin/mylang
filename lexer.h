#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>

typedef enum {
    BEGINNING,
    INT,
    KEYWORD,
    SEPARATOR,
    OPERATOR,
    END_OF_TOKENS,
}TokenType;

typedef struct {
    TokenType type;
    char *value;

}Token;

void print_token(Token token);
Token generate_number(char *,int*);
Token *generate_keyword(char*,int*);
Token *generate_separator_or_operator(char*,int*,TokenType);
Token *lexer(FILE*);

#endif // LEXER_H
