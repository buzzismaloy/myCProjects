#include "stack.h"
#include <string.h>
#include <ctype.h>
#define MAX_LENGTH 257
#define INVALID_OPERATOR_ERR -3
#define INVALID_RPN_ERR -4

char user_input[MAX_LENGTH];

/*void free_stack(Stack* stack){
    free(stack);
}*/

bool is_valid_char(char c){
    return isdigit(c) || c == '.' || c == '+' || c == '-' || c == '/' || c == '*' || c == ' ';
}

bool check_valid_str(const char* str){
    for(int i = 0; str[i] != '\0'; ++i){
        if(!is_valid_char(str[i])) return false;
    }

    return true;
}

bool check_decimal_points(const char* str){
    char* expression = strdup(str);
    if(expression == NULL){
        printf("Memory allocation failed!\n\n");
        exit(EXIT_FAILURE);
    }

    char* token = strtok(expression, " ");
    while(token){
        int dot_counter = 0;
        for(int i = 0; token[i] != '\0'; ++i){
            if(token[i] == '.'){
                dot_counter++;
                
                if(i == 0 || token[i + 1] == '\0'){
                    free(expression);
                    return false;
                }
            }
        }
        if(dot_counter > 1){
            free(expression);
            return false;
        }
        token = strtok(NULL, " ");
    }

    free(expression);
    return true;
}

bool check_spaces(const char* str){
    char* expression = strdup(str);
    if(expression == NULL){
        printf("Memory allocation failed!\n\n");
        exit(EXIT_FAILURE);
    }

    char* token = strtok(expression, " ");
    while(token){
        for(int i = 0; token[i] != '\0'; ++i){
            if(!isdigit(token[i]) && token[i] != '.'){
                if(strlen(token) != 1 && !strchr("+-/*", token[i])){
                    free(expression);
                    return false;
                }
            }
        }

        token = strtok(NULL, " ");
    }

    free(expression);
    return true;    
}

void make_operation(Stack* stack, char operation){
    double b = stack_pop(stack);
    double a = stack_pop(stack);

    switch(operation){
        case '+':
            stack_push(stack, a + b);
            break;
        case '-':
            stack_push(stack, a - b);
            break;
        case '*':
            stack_push(stack, a * b);
            break;
        case '/':
            if(b == 0){
                printf("Division by zero detected, error!\n\n");
                free(stack);
                exit(EXIT_FAILURE);
            }
            stack_push(stack, a / b);
            break;
    }
}

double parse_expression(char* str, Stack* stack){
    char* token = strtok(str, " ");

    while(token){
        if(isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))){
            stack_push(stack, atof(token));
        }
        else if(strchr("+-/*", token[0]) && strlen(token) == 1){
            if(stack->top < 1){
                printf("Invalid RPN expression!\n\n");
                return INVALID_RPN_ERR;
            }

            make_operation(stack, token[0]);
        }
        else{
            printf("Invalid operator: %s\n\n", token);
            return INVALID_OPERATOR_ERR;
        }

        token = strtok(NULL, " ");
    }

    if(stack->top != 0){
        printf("Invalid RPN!\n\n");
        return INVALID_RPN_ERR;
    }

    double res = stack_pop(stack);
    free(stack);

    return res;
}

void start_rpn(){
    while(1){
    printf("Enter a string(up to %d characters)\n\n", MAX_LENGTH - 1);

    if(fgets(user_input, MAX_LENGTH, stdin) == NULL){
        printf("Error reading input\n\n");
        exit(EXIT_FAILURE);
    }

    if(user_input[0] == '\0' || user_input[0] == '\n'){
        printf("Empty input error\n\n");
        exit(EXIT_FAILURE);
    }

    user_input[strcspn(user_input, "\n")] = '\0';

    if(!check_valid_str(user_input)){
        printf("Invalid chars are detected!\n\n");
        continue;
    }

    if(!check_decimal_points(user_input)){
        printf("Invalid usage of decimal dots is detected!\n\n");
        continue;
    }

    if(!check_spaces(user_input)){
        printf("Invalid input format!\n\n");
        continue;
    }

    Stack* stack = initialize_stack();
    double res = parse_expression(user_input, stack);
    if (res == INVALID_OPERATOR_ERR || res == INVALID_RPN_ERR) {
        free(stack);
        exit(EXIT_FAILURE);
    }
    printf("\n\nResult is: %lf\n",res);
    }
    
}


void menu(){
    printf("Hello, this is a calc for RPN expressions\n");
    printf("List of allowed characters: numbers(both int and double, to enter double use dot, e.g: 3.5), +, -, /, *, space\n");
    printf("You must enter operators and operands separated by 1 space, e.g: 3 4 + stands for 3 + 4 which equals 7\n");
    start_rpn();
}