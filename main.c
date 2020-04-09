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
    //TODO: Defensive programming and edge cases

    // declaration of the players and the board
    player players[PLAYERS_NUM];
    square board[BOARD_SIZE][BOARD_SIZE];
    initialize_players(players);
    initialize_board(board);

    print_board(board);

//    board[1][3] = *pushStack( &board[1][2], &board[1][3]);
//    printf("Size of [1][3] -> %d\n",get_stack_count(&board[1][3]));
//    print_board(board);


    int gameState = 0; // gameState represents the game phase 0 - in game/start game, 1-end game
    int num_of_rounds = 0;

    //TODO: Start game loop
    while (gameState==0 || num_of_rounds == 3){
        //TODO: NEXT PLAYERS TURN
        int turn = num_of_rounds % PLAYERS_NUM;

        //Display Instructions
//        display_instructions(0);
        //TODO: MAKE MOVE
        MakeMove(board,players[turn]);
        print_board(board);
//        int win = check_win(board);
        num_of_rounds++;


        //TODO: ASK USER FOR MOVE
        //TODO: FOLLOW UP ON MOVE (IF NEEDED)
        //TODO: CHECK WIN
//        gameState = 1;


    }



    print_board(board);






    print_board(board);
    return 0;
}

