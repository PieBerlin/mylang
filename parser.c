#include "parser.h"


void print_tree(Node *node,int indent,char *identifier){
    if (node == NULL){
        return ;
    }
    for ( int i = 0; i < indent; i++){
        printf(" ");
    }
    printf("%s -> ",identifier);
    for (size_t i = 0; node->value[i] != '\0'; i++){
        printf("%c",node->value[i]);
    }
    printf("\n");
    print_tree(node->left,indent + 1,"left");
    print_tree(node->right,indent + 1,"right");
}

Node *init_node(char *value,TokenType type){
    Node *node = malloc(sizeof(Node));
    node->value = malloc(sizeof(char ) * 2);
    node->value = value;
    node->type = type;
    node->left = NULL;
    node->right = NULL;

    return node;
}

void print_error(char *error_type){
    printf("ERROR: %s\n",error_type);
    exit(1);
}
void generate_operation_nodes(Token *current_token,Node *current_node){
    Node *oper_node = init_node(current_token->value,OPERATOR);
    current_node->left->left = oper_node;
    current_token--;
    while(current_token->type == INT || current_token->type == OPERATOR){
        if (current_token->type == INT){
            Node *expr_node = init_node(current_token->value,INT);
            oper_node->left = expr_node;
            current_token++;
            current_token++;

            if(current_token ->type != INT || current_token == NULL ){
                print_error("Syntax error");
                exit(1);
            }
            Node *second_expr_node = init_node(current_token->value,INT);
            oper_node->right = second_expr_node;
        }
        if (current_token->type == OPERATOR){

        }
        current_token++;
    }

}

Node *parser(Token *tokens){
    Token *current_token = &tokens[0];
    Node *root = init_node("PROGRAM",BEGINNING);



    Node *current = root;
    while (current_token->type != END_OF_TOKENS){
        if (current == root){
            // printf("root\n");
        }

        switch (current_token->type){
            case KEYWORD:
                if (strcmp(current_token->value, "EXIT") == 0){
                    Node *exit_node = init_node(current_token->value,KEYWORD);
                    root -> right = exit_node;
                    current = exit_node;
                    current_token ++;
                    if (current_token->type == END_OF_TOKENS){
                        print_error("Invalid Syntax expected '(' \n");
                    }
                    if (strcmp(current_token->value , "(") == 0 && current_token->type == SEPARATOR){
                        Node *open_paren_node = init_node(current_token->value,SEPARATOR);
                        current->left = open_paren_node;
                        current_token++;
                        if (current_token->type == END_OF_TOKENS){
                            print_error("Invalid Syntax on INT\n");
                        }
                        if (current_token-> type == INT){
                            current_token++;
                            if(current_token->type == OPERATOR && current_token != NULL){
                                generate_operation_nodes(current_token,current);
                                current_token++;
                            }else{
                                current_token--;
                                Node *expr_node = init_node(current_token->value,INT);
                                current->left->left = expr_node;

                            }
                            current_token++;
                            if (current_token->type == END_OF_TOKENS){
                                print_error("Invalid Syntax on ')'\n");
                            }
                            if (strcmp(current_token->value,")") == 0 && current_token->type == SEPARATOR){
                                Node *close_paren_node = init_node(current_token->value,SEPARATOR);
                                current->left->right = close_paren_node;
                                current_token++;
                                if (current_token->type == END_OF_TOKENS){
                                    print_error("Invalid Syntax expected ';' \n");
                                }
                                if (strcmp(current_token->value, ";") == 0 && current_token->type == SEPARATOR){
                                    Node *semi_node = init_node(current_token->value,SEPARATOR);
                                    current->right = semi_node;
                                    break;
                                }else{
                                    print_error("Invalid Syntax ON SEMI\n");
                                }

                            }else{
                                print_error("Invalid Syntax ON CLOSE\n");
                            }
                        }else{
                            print_error("Invalid Syntax ON INT\n");
                            exit(1);
                        }

                    }else{
                        print_error("Invalid Syntax ON OPEN\n");
                        exit(1);
                    }
                }


                break;
            case SEPARATOR:
                break;
            case OPERATOR:
                break;
            case INT:
                break;
            case BEGINNING:
                break;

            default:
                break;

        }
        


       current_token++; 
    }
    print_tree(root,0,"root");

    return root;
}

