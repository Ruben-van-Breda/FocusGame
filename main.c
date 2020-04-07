//
// Created by Lili on 26/03/2020.
//

#include <stdio.h>
#include <stdlib.h>

#include "input_output.h"
#include "GameBoard.h"
#include <fcntl.h>
#include <zconf.h>
#include <wchar.h>

int main() {

    // declaration of the players and the board
    player players[PLAYERS_NUM];
    square board[BOARD_SIZE][BOARD_SIZE];
    initialize_players(players);
    initialize_board(board);

    printf("count = %d ",get_stack_count(board[1][2].stack));
    //START GAME
    board[1][2].stack = push(RED,board[1][2].stack);

    printf("count = %d",get_stack_count(board[1][2].stack));

    print_board(board);
    return 0;
}
//
//void GUI(){
////    setmode(STDOUT_FILENO);
//    wprintf(L"\x043a");
//}
