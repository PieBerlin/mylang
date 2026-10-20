#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "lexer.h"


Token *generate_number(char  *buffer,int *curr_indx){
    Token *token = malloc(sizeof(Token));
    token->type = INT;
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
        (*curr_indx)++;
        current = buffer[*curr_indx];
    }
    // token.value = value;
    int size = strlen(TO_STRING(value)) + 1;
    token->value = malloc(size);
    snprintf(token->value, size, "%d",value);
    token->value[size + 1] ='\0'; 
    return token;
}

Token *generate_keyword(char *buffer,int *curr_indx){
    Token *token = malloc(sizeof(Token));
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
        token->type = KEYWORD;
        token->value = "EXIT";
    }

    return token;
}

Token *generate_separator_or_operator(char *buffer,int *curr_indx,TokenType type){
    Token *token = malloc(sizeof(Token));
    token->value = malloc(sizeof(char) * 2);
    token->value[0] = buffer[*curr_indx];
    token->value[1] = '\0';
    token->type = type;
    return token;
        
}

void print_token(Token token){
    printf("TOKEN VALUE: ");
    printf(" '");
    for (int i = 0; token.value[i] != '\0';i++){
        printf("%c",token.value[i]);
    }
    printf("' ");

    switch (token.type){
        case INT:
            printf("TOKEN TYPE : INT\n");
            break;
        case KEYWORD:
            printf("TOKEN TYPE: KEYWORD\n");
            break;
        case SEPARATOR:
            printf("TOKEN TYPE SEPARATOR\n");
            break;
        case OPERATOR:
            printf("TOKEN TYPE : OPERATOR \n");
            break;
        case END_OF_TOKENS:
            printf("END OF TOKENS\n");
            break;
        case BEGINNING:
            printf("BEGINNING \n");
    }
}

size_t tokens_index; 

Token *lexer(FILE *file){
    long length ;

    char *buffer ;
    fseek(file,0,SEEK_END);
    length = ftell(file);
    fseek(file,0,SEEK_SET);

    buffer = malloc((sizeof(char) * length) + 1);
    fread(buffer,1,length,file);
    fclose(file);
    buffer[length + 1] = '\0';

    int *curr_indx = (int*)malloc(sizeof(int));
    *curr_indx = 0;

    Token *tokens = malloc(sizeof(Token));
    tokens_index = 0;

    while(buffer[*curr_indx] != '\0'){
        Token *token = malloc(sizeof(Token));
        if (buffer[*curr_indx] == ';'){
            token = generate_separator_or_operator(buffer,curr_indx,SEPARATOR);
            tokens[tokens_index] = *token;
            tokens_index++;
            *curr_indx += 1;
        }else if (buffer[*curr_indx] == '('){
            token = generate_separator_or_operator(buffer,curr_indx,SEPARATOR);
            tokens[tokens_index] = *token;
            tokens_index++;
            *curr_indx += 1;
        }else if (buffer[*curr_indx] == ')'){
            token = generate_separator_or_operator(buffer,curr_indx,SEPARATOR);
            tokens[tokens_index] = *token;
            tokens_index++;
            (*curr_indx)++;
        }else if (buffer[*curr_indx] == '+') {
            token = generate_separator_or_operator(buffer,curr_indx,OPERATOR);
            tokens[tokens_index] = *token;
            tokens_index++;
            *curr_indx += 1;

        }
        else if (isdigit(buffer[*curr_indx])){
            token = generate_number(buffer,curr_indx);
            tokens[tokens_index] = *token;
            tokens_index ++;
        }else if (isalpha(buffer[*curr_indx])){
            token = generate_keyword(buffer,curr_indx);
            tokens[tokens_index] = *token;
            tokens_index++;
        }
        else{
            break;
        }
        free(token);
    }

    free(curr_indx);
    tokens[tokens_index].value ='\0';
    tokens[tokens_index].type = END_OF_TOKENS;
    return tokens;

}



