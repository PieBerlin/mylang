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

TokenLiteral generate_number(char  *buffer,int *curr_indx){
    TokenLiteral token;
    token.type = INT;
    int value = buffer[*curr_indx] - '0';
    (*curr_indx)++;
    char current = buffer[*curr_indx];
    while (isdigit(current) && current != '\0'){
        if(!isdigit(current)){
            printf("\n");
            break;
        }
        value *= 10;
        value += current - '0';
        // printf("%c",current);
        (*curr_indx)++;
        current = buffer[*curr_indx];
    }
    token.value = value;
    return token;
}

TokenKeyword *generate_keyword(char *buffer,int *curr_indx){
    TokenKeyword *token = malloc(sizeof(TokenKeyword));
    char *keyword = malloc(sizeof(char) * 5);
    int keyword_index = 0;
    keyword[keyword_index] = buffer[*curr_indx];
    keyword_index ++;
    (*curr_indx)++;
    while(isalpha(buffer[*curr_indx]) && buffer[*curr_indx] != '\0'){
        keyword[keyword_index] = buffer[*curr_indx];
        keyword_index++;
        (*curr_indx)++;
    }
    keyword[keyword_index]='\0';
    if (strcmp(keyword, "exit") == 0){
        token->type = EXIT;
    }else{
        token->type = IDENT;
    }

    return token;
}

void lexer(FILE *file){
    long length ;

    char *buffer ;
    fseek(file,0,SEEK_END);
    length = ftell(file);
    fseek(file,0,SEEK_SET);

    buffer = malloc(sizeof(char) * length);
    fread(buffer,1,length,file);
    fclose(file);
    buffer[length] = '\0';

    int *curr_indx = (int*)malloc(sizeof(int));
    *curr_indx = 0;

    while(buffer[*curr_indx] != '\0'){
        if (buffer[*curr_indx] == ';'){
            printf("FOUND SEMICOLON\n");
            (*curr_indx)++;
        }else if (buffer[*curr_indx] == '('){
            printf("FOUND OPEN PAREN\n");
            (*curr_indx)++;
        }else if (buffer[*curr_indx] == ')'){
            printf("FOUND CLOSE PAREN\n");
            (*curr_indx)++;
        }else if (isdigit(buffer[*curr_indx])){
            TokenLiteral test_token= generate_number(buffer,curr_indx);
            printf("TEST TOKEN VALUE : %d\n",test_token.value);
        }else if (isalpha(buffer[*curr_indx])){
            TokenKeyword *test_token = generate_keyword(buffer,curr_indx);
            printf("TEST TOKEN %d\n",test_token->type);

            // printf("FOUNC CHARACTER: %c\n",current);
        }
        else if (buffer[*curr_indx] == '\n') {
            printf("FOUND NEW LINE\n\n");
            (*curr_indx)++;
        }
    }

    free(curr_indx);

}
int main(){
    FILE *file;
    file = fopen("test.mlg","r");

    lexer(file);
    

}
