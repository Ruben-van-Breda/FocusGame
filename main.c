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
square board[BOARD_SIZE][BOARD_SIZE];
int main() {

    // declaration of the players and the board
    player players[PLAYERS_NUM];
//    square board[BOARD_SIZE][BOARD_SIZE];
    initialize_players(players);
    initialize_board(board);
    int winner = -1;

    //MAKE DEBUG EASIER
    players[0].own_pieces = 4;

    /*board[1][1].stack = NULL;
    board[1][2].stack = NULL;
    board[1][3].stack = NULL;
    board[1][4].stack = NULL;
    board[1][5].stack = NULL;
    board[1][6].stack = NULL;

    board[2][1].stack = NULL;
    board[2][2].stack = NULL;
    board[2][3].stack = NULL;
    board[2][4].stack = NULL;
    board[2][5].stack = NULL;
    board[3][1].stack = NULL;
    board[3][2].stack = NULL;
    board[3][3].stack = NULL;
    board[3][4].stack = NULL;
    board[3][5].stack = NULL;
    board[4][1].stack = NULL;
    board[4][4].stack = NULL;
    board[4][3].stack = NULL;
    board[4][2].stack = NULL;
    board[4][5].stack = NULL;
    board[5][1].stack = NULL;
    board[5][2].stack = NULL;
    board[5][3].stack = NULL;
    board[5][4].stack = NULL;
    board[5][5].stack = NULL;
    board[5][6].stack = NULL;
    board[6][1].stack = NULL;
    board[6][2].stack = NULL;
    board[6][3].stack = NULL;
    board[6][4].stack = NULL;
    board[6][5].stack = NULL;
    board[6][6].stack = NULL;*/



    players[0].own_pieces = 4;

    print_board(board);


    int gameState = 0; // gameState represents the game phase 0 - in game/start game, 1-end game
    int num_of_rounds = 0;

    //TODO: Start game loop
    while (gameState == 0 || num_of_rounds < 3){
        //TODO: NEXT PLAYERS TURN
        int turn = num_of_rounds % PLAYERS_NUM;

        //TODO: MAKE MOVE
        MakeMove(board,players[turn],false);
        int loser = can_player_move(board);
        if(loser == -1){
            //All fine play on
        }
        if(loser != -1){
            print_board(board);
            //Check if that player has any reserves to play
            printf("%s, no where to play?...\n",players[loser].name);
            printf("%s you have %d pieces in reserves.\n",players[loser].name,players[loser].own_pieces);
            if(players[loser].own_pieces == 0){
                //TODO: GAME OVER
                if(loser==0){winner=1;}
                else if(loser == 1){winner=0;}
                gameState = 1;
            }
            else{
                //play a reserve onto table
                MakeMove(board,players[loser],true);
                num_of_rounds++;
            }
        }
        print_board(board);



        num_of_rounds++;

    }
    /*  We have a winner   */
    if(winner != -1){
        printf("\n\n_____GAME_OVER______\n");
        printf("%s coloured %s WINS with %d captured pieces\n",players[winner].name,players[winner].player_color?"green":"red",players[winner].adversary);

    }

    return 0;
}



