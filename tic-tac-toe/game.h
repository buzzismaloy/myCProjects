#pragma once
#include "player.h"
#include "game_check.h"
#include "bot_algo.h"
#include <time.h>
#include <signal.h>

const char PLAYER_1 = 'X', PLAYER_2 = 'O';

int need_to_free = 0;

void signal_handler(int sign_num){
    need_to_free = 1;
}

void clear_input(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

void clear_terminal(){
    printf("\x1b[2J");
}

void menu(){
    //clear_terminal();
    printf("To start game player vs player, press 1\nTo start game player vs bot, press 2\nTo quit, press 0\n\n");
}

void quit(){
    clear_terminal();
    printf("Goodbye!\n\n");
    exit(0);
}

void free_memory(Player* player_1, Player* player_2){
    free(player_1);
    free(player_2);
}

Player* create_player(const char* name, const char symbol){
    Player* player = (Player*)malloc(sizeof(Player));
    if(player == NULL){
        printf("Memory allocation failure!\n\n");
        exit(EXIT_FAILURE);
    }

    initialize_player(player, name, symbol);

    return player;
}

int scan_cell(int* i, int* j){
        printf("Please, enter the indexes(separated by space) of the cell in which you want to put your symbol.\n");
        printf("Please, pay attention that this cell must not be filled!\n");
        int res;
        res = scanf("%d %d", i, j);
        
        if(res != 2){
            printf("Invalid input!\n\n");
            clear_input();

            return 0;
        }

        if(*i < 0 || *i > 2 || *j < 0 || *j > 2){
            printf("Your numbs cant be out of range!!!\n\n");
            clear_input();

            return 0;
        }

        return 1;
}

void player_vs_player(){
    signal(SIGINT, signal_handler);

    clear_terminal();
    Player* player_1;
    Player* player_2;
    char name[MAX_NAME_LENGTH];

    printf("Please, enter your username, first player:\n\n");
    fgets(name, sizeof(name), stdin);
    if(name[strlen(name) - 1] == '\n') name[strlen(name) - 1] = '\0';
    player_1 = create_player(name, PLAYER_1);
    display_player(player_1);

    printf("Please, enter your username, second player:\n\n");
    fgets(name, sizeof(name), stdin);
    if(name[strlen(name) - 1] == '\n') name[strlen(name) - 1] = '\0';
    player_2 = create_player(name, PLAYER_2);
    display_player(player_2);

    draw_board();
    while(1){
        int i, j;
        if(turn_flag){
            printf("\n%s turn:\n\n", player_1->name);
            if(!scan_cell(&i, &j)){
                printf("Try again!\n\n");
                continue;
            }

            int scan_res = make_turn(i, j, player_1->symbol);
            if(!scan_res){
                printf("Try again!\n\n");
                continue;
            }

            int res = check_board(SIZE, board);
            if(res == DRAW){
                printf("\nIt's draw!\n\n");
                display_player(player_1);
                display_player(player_2);

                break;
            }
            else if(res == SUCCESS){
                printf("\nPlayer 1 won!\n\n");
                display_player(player_1);

                break;
            }

        }
        else{
            printf("\n%s turn:\n\n", player_2->name);
            if(!scan_cell(&i, &j)){
                printf("Try again!\n\n");
                continue;
            }

            int scan_res = make_turn(i, j, player_2->symbol);
            if(!scan_res){
                printf("Try again!\n\n");
                continue;
            }

            int res = check_board(SIZE, board);
            if(res == DRAW){
                printf("\nIt's draw!\n\n");
                display_player(player_1);
                display_player(player_2);

                break;
            }
            else if(res == SUCCESS){
                printf("\nPlayer 2 won!\n\n");
                display_player(player_1);

                break;
            }
        }

        if(need_to_free) {
            free_memory(player_1, player_2);
            return;
        }
    }

    free_memory(player_1, player_2); 
}

void player_vs_bot(){
    signal(SIGINT, signal_handler);

    clear_terminal();
    Player* player_1;
    Player* bot;
    char name[MAX_NAME_LENGTH];

    printf("Please, enter your username, first player:\n\n");
    fgets(name, sizeof(name), stdin);
    if(name[strlen(name) - 1] == '\n') name[strlen(name) - 1] = '\0';
    player_1 = create_player(name, PLAYER_1);
    display_player(player_1);

    bot = create_player(BOT_NAME, PLAYER_2);
    display_player(bot);

    draw_board();
    while(1){
        if(turn_flag){
            int i, j;
            printf("\n%s turn:\n\n", player_1->name);
            if(!scan_cell(&i, &j)){
                printf("Try again!\n\n");
                continue;
            }

            int scan_res = make_turn(i, j, player_1->symbol);
            if(!scan_res){
                printf("Try again!\n\n");
                continue;
            }

            int res = check_board(SIZE, board);
            if(res == DRAW){
                printf("\nIt's draw!\n\n");
                display_player(player_1);
                display_player(bot);

                break;
            }
            else if(res == SUCCESS){
                printf("\nPlayer 1 won!\n\n");
                display_player(player_1);

                break;
            }
        }
        else{
            bot_algo(bot->symbol, player_1->symbol);
            int res = check_board(SIZE, board);
              if(res == DRAW){
                printf("\nIt's draw!\n\n");
                display_player(player_1);
                display_player(bot);

                break;
            }
            else if(res == SUCCESS){
                printf("\nBot won!\n\n");
                display_player(bot);

                break;
            }
        }

        if(need_to_free) {
            free_memory(player_1, bot);
            return;
        }
    
    }

    free_memory(player_1, bot);
}

void check_game_mode(){
    int choice;
    set_board();
    while(1){
        int result = scanf("%d", &choice);
        if(!result){
            printf("Invalid input error!\n\n");
            return;
        }

        clear_input();
        switch(choice){
            case 0:
                quit();
            case 1:
                player_vs_player();
                return;
            case 2:
                player_vs_bot();
                return;
            default:
                printf("Invalid input, try again!\n\n");
    }
    }

}

void run(){
    srand(time(NULL));
    printf("Welcome to my tic-tac-toe game!\n\n");

    while(1){
    menu();
    check_game_mode();
    clear_input();
    }

}