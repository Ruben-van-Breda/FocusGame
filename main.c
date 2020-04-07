//
// Created by Lili on 26/03/2020.
//

#include <stdio.h>
#include <stdlib.h>

#include "input_output.h"
#include "GameLogic.h"
#include <fcntl.h>
#include <zconf.h>
#include <wchar.h>

int main() {

    // declaration of the players and the board
    player players[PLAYERS_NUM];
    square board[BOARD_SIZE][BOARD_SIZE];
    initialize_players(players);
    initialize_board(board);

    print_board(board);


    //START GAME
    board[1][2].stack = push(GREEN,board[1][2].stack);
    board[1][2].stack = push(RED,board[1][2].stack);
//    board[1][2].stack = push(GREEN,board[1][2].stack);
//    board[1][3].stack = push(GREEN,board[1][3].stack);
    board[1][3].stack = push(GREEN,board[1][3].stack);
    board[1][3].stack = push(GREEN,board[1][3].stack);

    print_board(board);


    printStack(board[1][2].stack,"Stack[1][2]->");
    printStack(board[1][3].stack,"Stack[1][3]->");

    board[1][3] = *pushStack( &board[1][3], &board[1][2]);
    printStack(board[1][3].stack,"Stack[1][3]->");
    printf("get_stack_count [1][3] = %d",get_stack_count(board[1][3].stack));




    print_board(board);
    return 0;
}
//
//void GUI(){
////    setmode(STDOUT_FILENO);
//    wprintf(L"\x043a");
//}
