/*testfile.c 
 * This file is for testing independent functions separately */
#include <stdio.h>
#include "lexer.h"

int main(){

    int var = 13243;

    printf("%s\n",TO_STRING(var));
    return 0;
}
