#pragma once
#include "field.h"
#include <string.h>
#define TURN_SUCCESS 1
#define TURN_FAILURE 0
#define MAX_NAME_LENGTH 20

typedef struct{
    char name[MAX_NAME_LENGTH];
    char symbol;
} Player;

void initialize_player(Player* player, const char* name, char symbol){
    strcpy(player->name, name);
    player->symbol = symbol;
}

void display_player(Player* player){
    printf("Player: %s, symbol: %c\n\n", player->name, player->symbol);
}

int make_turn(int pos_x, int pos_y, char symbol){
    if(board[pos_x][pos_y] != ' '){
        printf("You cant put your symbol in the filled cell!\n\n");
        return TURN_FAILURE;
    }

    board[pos_x][pos_y] = symbol;
    turn_flag = !turn_flag;
    draw_board();

    return TURN_SUCCESS;
}