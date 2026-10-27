/* codegenerator.c */
#include "codegenerator.h"
#include "./hashmap/hashmap.h"


void traverse_tree(Node *node,FILE *file){
    if (node == NULL)
        return;
    if (strcmp(node->value ,"EXIT") == 0)
        fprintf(file, "\tmov rax, 60\n");
    if (node->type == OPERATOR){
        // printf("%s\n",node->value);
        fprintf(file, "\tmov rdi, %s\n",node->left->value);
        Node *tmp = node;
        while(tmp->right->type == OPERATOR ){
            char *oper = search(tmp->value[0])->data;
            tmp = tmp->right;
            fprintf(file, "\t%s rdi, %s\n",oper,tmp->left->value);
        }
        fprintf(file, "\t%s rdi, %s\n",search(tmp->value[0])->data,tmp->right->value);
        node->left = NULL;
        node->right = NULL;
    }
    if(node->type  == INT) 
        fprintf(file, "\tmov rdi, %s\n",node->value);
    
    if (strcmp(node->value,";") == 0)
        fprintf(file, "\tsyscall");
    traverse_tree(node->left,file);
    traverse_tree(node->right,file);
}
int generate_code(Node *root){
    insert('-',"sub");
    insert('+',"add");
    FILE *file = fopen("generated.asm","w+");
    assert(file != NULL && "FILE COULD NOT BE OPENED");

    fprintf(file,"section .text\n");
    fprintf(file, "\tglobal _start\n");
    fprintf(file,"_start:\n");


    traverse_tree(root,file);
    fclose(file);
    return 0;
}
