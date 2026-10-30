/* codegenerator.c */
#include "codegenerator.h"
#include "./hashmap/hashmap.h"

Node* generate_operator_code(Node *node,int syscall_number,FILE *file){
    fprintf(file, "\tmov rax, %s\n",node->left->value);
    Node *tmp = node;
    int did_loop = 0;
    while(tmp->right->type == OPERATOR ){
        did_loop = 1;
        char *oper = search(tmp->value[0])->data;
        tmp = tmp->right;
        fprintf(file, "\tmov rbx, %s\n",tmp->left->value);
        if (strcmp(oper,"mul") == 0 || strcmp(oper,"div") == 0){
            fprintf(file, "\t%s rbx\n",oper);
            fprintf(file, "\tmov rdi, rax\n");
        }else{
            fprintf(file, "\t%s rax, rbx\n",oper);
            fprintf(file, "\tmov rdi, rax\n");
        }
    }
    if (did_loop){
        if(tmp->value[0] == '*' || tmp->value[0] == '/'){
            fprintf(file, "\tmov rax, rdi\n");
            fprintf(file, "\tmov rbx, %s\n",tmp->right->value);
            fprintf(file, "\t%s rbx\n",search(tmp->value[0])->data);
            fprintf(file, "\tmov rdi, rax\n");
        }
        else{
            fprintf(file, "\t%s rdi, %s\n",search(tmp->value[0])->data,tmp->right->value);
        }
    }
    else{
        fprintf(file, "\tmov rbx, %s\n",tmp->right->value);
        fprintf(file, "\t%s rbx\n",search(tmp->value[0])->data);
        fprintf(file, "\tmov rdi,rax\n");
    }
    fprintf(file, "\tmov rax , %d\n",syscall_number);
    node->left = NULL;
    node->right = NULL;

    return node;

}

void traverse_tree(Node *node,FILE *file,int syscall_number){
    if (node == NULL)
        return;
    if (strcmp(node->value ,"EXIT") == 0){
        syscall_number = 60;
        // fprintf(file, "\tmov rax, 60\n");
    }
    if (node->type == OPERATOR){
        generate_operator_code(node,syscall_number,file);

    }
    if(node->type  == INT) 
        fprintf(file, "\tmov rdi, %s\n",node->value);
    
    if (strcmp(node->value,";") == 0)
        fprintf(file, "\tsyscall");
    traverse_tree(node->left,file,syscall_number);
    traverse_tree(node->right,file,syscall_number);
}
int generate_code(Node *root){
    insert('-',"sub");
    insert('+',"add");
    insert('*',"mul");
    insert('/',"div");
    FILE *file = fopen("generated.asm","w+");
    assert(file != NULL && "FILE COULD NOT BE OPENED");

    fprintf(file,"section .text\n");
    fprintf(file, "\tglobal _start\n");
    fprintf(file,"_start:\n");


    traverse_tree(root,file,60);
    fclose(file);
    return 0;
}
