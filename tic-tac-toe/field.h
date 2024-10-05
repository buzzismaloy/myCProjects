#pragma once
#include <stdio.h>
#define SIZE 3

char board[SIZE][SIZE];

int turn_flag = 1;

void set_board(){
    turn_flag = 1;
    for(int i = 0; i < SIZE; ++i){
        for(int j = 0; j < SIZE; ++j)
            board[i][j] = ' ';
    }
}

void draw_board(){
    printf("  0 1 2\n");
    for(int i = 0; i < SIZE; ++i){
        
        printf("%d ", i);
        for(int j = 0; j < SIZE; ++j){
            printf("%c", board[i][j]);

            if(j < SIZE - 1) printf("|");
        }
        printf("\n");
        if(i < SIZE - 1) printf("  -----\n");
    }
}