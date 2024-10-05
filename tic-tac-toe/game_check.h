#pragma once
#define DRAW -1
#define SUCCESS 1
#define NOTHING 0

int check_horizontal(int size, char board[3][3]){
    int counter;

    for(int i = 0; i < size; ++i){
        counter = 1;
        if(board[i][0] == ' ') continue;

        for(int j = 1; j < size; ++j){
            if(board[i][j] == board[i][j - 1]) counter++;
            else break;
        }

        if(counter == size) return SUCCESS;
    }

    return NOTHING;
}

int check_vertical(int size, char board[3][3]){
    int counter;

    for(int j = 0; j < size; ++j){
        counter = 1;
        if(board[0][j] == ' ') continue;

        for(int i = 1; i < size; ++i){
            if(board[i][j] == board[i - 1][j]) counter++;
            else break;
        }

        if(counter == size) return SUCCESS;
    }

    return NOTHING;
}

int check_main_diagonal(int size, char board[3][3]){
    if(board[0][0] == ' ') return NOTHING;
    int counter = 1;

    for(int i = 1; i < size; ++i){
        if(board[i][i] == board[i - 1][i - 1]) counter++;
        else break;
    }

    if(counter == size) return SUCCESS;

    return NOTHING;
}

int check_side_diagonal(int size, char board[3][3]){
    if(board[0][size - 1] == ' ') return NOTHING;
    int counter = 1;
    for(int i = 1; i < size; ++i){
        if(board[i][size - i - 1] == board[i - 1][size - i]) counter++;
        else break;
    }

    if(counter == size) return SUCCESS;

    return NOTHING;
}

int check_spaces(int size, char board[3][3]){
    for(int i = 0; i < size; ++i){
        for(int j = 0; j < size; ++j){
            if(board[i][j] == ' ') return 1;
        }
    }

    return 0;
}

int check_board(int size, char board[3][3]){
    int res = check_horizontal(size, board) + check_vertical(size, board) + check_main_diagonal(size, board) 
        + check_side_diagonal(size, board);

    if(!res){
        if(!check_spaces(size, board)) return DRAW;
        return NOTHING;
    }

    return SUCCESS;
}
