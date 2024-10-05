#pragma once
#include "player.h"
#include "field.h"
#include "game_check.h"
#include <stdlib.h>

const char* BOT_NAME = "Computer";

void print_turn(int i, int j){
    printf("\n%s moved to %d %d\n\n", BOT_NAME, i, j);
}

void make_random_move(char symbol){
    int i, j;

    do{
        i = rand() % SIZE;
        j = rand() % SIZE;
    }while(board[i][j] != ' ');

    print_turn(i, j);
    make_turn(i, j, symbol);
}

int make_center_move(char symbol){
    if(board[SIZE / 2][SIZE / 2] == ' '){
        print_turn(SIZE / 2, SIZE /2);
        make_turn(SIZE / 2, SIZE / 2, symbol);
        return 1;
    }
    return 0;
}

int block_enemy_turn(char bot_symbol, char human_symbol){
    for(int i = 0; i < SIZE; ++i){
        for(int j = 0; j < SIZE; ++j){
            if(board[i][j] == ' '){
                board[i][j] = human_symbol;
                
                int human_turn = check_board(SIZE, board);
                if(human_turn == SUCCESS){
                    print_turn(i, j);
                    board[i][j] = bot_symbol;
                    return 1;
                }

                board[i][j] = ' ';
            }
        }
    }

    return 0;
}

int make_winning_move(char symbol){
    for(int i = 0; i < SIZE; ++i){
        for(int j = 0; j < SIZE; ++j){
            if(board[i][j] == ' '){
                board[i][j] = symbol;

                int res = check_board(SIZE, board);
                if(res == SUCCESS) {
                    print_turn(i, j);
                    return 1;
                }

                board[i][j] = ' ';
            }
        }
    }

    return 0;
}

void bot_algo(char bot_symbol, char human_symbol){
    int turn = make_center_move(bot_symbol);
    if(turn) return;
    
    turn = block_enemy_turn(bot_symbol, human_symbol);
    if(turn){
        turn_flag = !turn_flag;
        draw_board();
        return;
    }

    turn = make_winning_move(bot_symbol);
    if(turn){
        turn_flag = !turn_flag;
        draw_board();
        return;
    }

    make_random_move(bot_symbol);
}