#include "parser.h"


void print_tree(Node *root){
    if (root == NULL){
        return;
    }

    printf("root: %s\n",root->value);
    print_tree(root->left);
    print_tree(root->right);
}

Node *init_node(char *value,NodeType type){
    Node *node = malloc(sizeof(Node));
    node->value = malloc(sizeof(char ) * 2);
    node->value = value;
    node->type = type;
    node->left = NULL;
    node->right = NULL;

    return node;
}


Token *parser(Token *tokens){
    Token *current_token = &tokens[0];
    Node *root = init_node("PROGRAM",BEGIN);



    Node *current = root;
    while (current_token->type != END_OF_TOKENS){
        if (current == root){
            // printf("root\n");
        }

        if (current_token-> type == KEYWORD && strcmp(current_token->value, "exit")){
            Node *exit_node = init_node(current_token->value,STATEMENT);
            root->right = exit_node;
            current = exit_node;
            current_token++;
            if (current_token->type !=  SEPARATOR ){
                printf("ERROR\n");
                exit(1);
            }

            Node *open_paren_node = init_node(current_token->value,SEP);
            current->left = open_paren_node;
            current_token++;

            Node *expr_node = init_node(current_token->value,INT_LIT);
            current->left->left = expr_node;
            current_token++;

            Node *close_paren_node = init_node(current_token->value,SEP);
            current->left->right = close_paren_node;
            current_token++;


            Node *semi_node = init_node(current_token->value,SEP);
            current->right = semi_node;
        


            printf("EXIT\n");
            break;

        }


       current_token++; 
    }
    print_tree(root);

    return current_token;
}

