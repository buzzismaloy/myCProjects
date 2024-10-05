#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define STD_MAX_CAPACITY 128
#define VOID_SIZE -1
#define STACK_UNDERFLOW_ERR -2

typedef struct{
    double array[STD_MAX_CAPACITY];
    int top;
} Stack;

Stack* initialize_stack(){
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if(!stack){
        printf("Memory allocation failed!\n\n");
        return NULL;
    }

    stack->top = VOID_SIZE;

    return stack;
}

bool stack_is_full(Stack* stack){
    return stack->top == STD_MAX_CAPACITY - 1;
}

void stack_push(Stack* stack, double value){
    if(stack_is_full(stack)){
        printf("Max capacity of stack has been reached!!!\n\n");
        return;
    }

    stack->array[++stack->top] = value; 
}

bool stack_is_empty(Stack* stack){
    return stack->top == VOID_SIZE;
}

double stack_pop(Stack* stack){
    if(stack_is_empty(stack)){
        printf("Stack underflow!!!\n\n");
        return STACK_UNDERFLOW_ERR;
    } 

    return stack->array[stack->top--];
}

double stack_peek(Stack* stack){
    if(stack_is_empty(stack)){
        printf("Stack underflow!!!\n\n");
        return STACK_UNDERFLOW_ERR;
    }

    return stack->array[stack->top];
}
