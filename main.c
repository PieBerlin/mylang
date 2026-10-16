#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef enum{
    SEMI,
    OPEN_PAREN,
    CLOSE_PAREN,

}TypeSeparator;

typedef enum {
    EXIT,
    IDENT,
}TypeKeyword;

typedef enum {
    INT,
}TypeLiteral;


typedef struct {
    TypeKeyword type;
}TokenKeyword;

typedef struct {
    TypeSeparator type;

}TokenSeparator;

typedef struct {
    TypeLiteral type;
    int value;

}TokenLiteral;

TokenLiteral generate_number(char current,FILE *file){
    TokenLiteral token;
    token.type = INT;
    int value = current - '0';
    current = fgetc(file);
    while (isdigit(current) && current != EOF){
        if(!isdigit(current)){
            printf("\n");
            break;
        }
        value *= 10;
        value += current - '0';
        // printf("%c",current);
        current = fgetc(file);
    }
    ungetc(current,file);/* return the char read if its not a number */
    token.value = value;
    return token;
}

TokenKeyword *generate_keyword(char character, FILE *file){
    TokenKeyword *token = malloc(sizeof(TokenKeyword));
    char *keyword = malloc(sizeof(char) * 4);
    char current = character;
    int keyword_index = 0;
    keyword[keyword_index] = character;
    keyword_index ++;
    current = fgetc(file);
    while(isalpha(current) && current != EOF){
        keyword[keyword_index] = current;
        current = fgetc(file);
        keyword_index++;
    }
    if (strcmp(keyword, (char*) "exit") == 0){
        token->type = EXIT;
    }else{
        token->type = IDENT;
    }
    ungetc(current,file);

    return token;
}

/*TODO: Read the entire file into a buffer instead of each character at a time...
 * This would speed up the lexer */
void lexer(FILE *file){
    char current = fgetc(file);

    while(current != EOF){
        if (current == ';'){
            printf("FOUND SEMICOLON\n");
        }else if (current == '('){
            printf("FOUND OPEN PAREN\n");
        }else if (current == ')'){
            printf("FOUND CLOSE PAREN\n");
        }else if (isdigit(current)){
            TokenLiteral test_token= generate_number(current,file);
            printf("TEST TOKEN VALUE : %d\n",test_token.value);
        }else if (isalpha(current)){
            TokenKeyword *test_token = generate_keyword(current,file);
            printf("TEST TOKEN %d\n",test_token->type);

            // printf("FOUNC CHARACTER: %c\n",current);
        }
        current = fgetc(file);
    }

}
int main(){
    FILE *file;
    file = fopen("test.mlg","r");

    lexer(file);
    

}
