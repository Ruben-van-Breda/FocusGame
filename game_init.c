//
// Created by Lili on 26/03/2020.
//

//
// Created by Lili on 24/03/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game_init.h"

#define MAX_CHAR 20

void initialize_players(player players[PLAYERS_NUM]){

    // implement here the functionality to initialize the players

    //: Loop through the players
    for (int i = 0; i < PLAYERS_NUM;  i++) {
        // Create a string for the players name
        char *name_input = (char*)malloc(sizeof(char)*MAX_CHAR);
        //Check that the memory was correctly allocated
        if(name_input==NULL){
            perror("Error: Memory was not allocated ");
        }

        //TODO: Get players name as input from user
        printf("Please enter player %d' name: ",i);
        scanf("%s",name_input);

        char c; // Char c is to store the current character in the name_input
        size_t name_len; // name_len is to store the length of the name the user inputted.
        for (name_len = 1; (c = name_input[name_len-1]) != '\0' && (c = name_input[name_len-1]) != ' '; name_len++); //determine the size of name_input
        players[i].name = (char*)malloc(sizeof(char)*name_len-1); //Allocate the memory to name
        // Initialise the values of player
        players[i].name = name_input;
        players[i].player_color = i; // Set the color of the player

    }
    // Put some text into the memory
//        strncpy(players[i].name, name_input,MAX_CHAR);


}

//Set Invalid Squares (where it is not possible to place stacks)
set_invalid(square * s){
s->type = INVALID;
s->stack = NULL;
s->num_pieces = 0;
}

//Set Empty Squares (with no pieces/stacks)
set_empty(square * s){
s->type = VALID;
s->stack = NULL;
s->num_pieces = 0;
}

//Set squares  with a GREEN piece
set_green(square * s){
s->type = VALID;
s->stack = (piece *) malloc (sizeof(piece));
s->stack->p_color = GREEN;
s->stack->next = NULL;
s->num_pieces = 1;
}

//Set squares with a RED piece
set_red(square * s){
s->type = VALID;
s->stack = (piece *) malloc (sizeof(piece));
s->stack->p_color = RED;
s->stack->next = NULL;
s->num_pieces = 1;
}

//initializes the board
void initialize_board(square board [BOARD_SIZE][BOARD_SIZE]){

    for(int i=0; i< BOARD_SIZE; i++){
        for(int j=0; j< BOARD_SIZE; j++){
            //invalid squares
            if((i==0 && (j==0 || j==1 || j==6 || j==7)) ||
               (i==1 && (j==0 || j==7)) ||
               (i==6 && (j==0 || j==7)) ||
               (i==7 && (j==0 || j==1 || j==6 || j==7)))
                set_invalid(&board[i][j]);

            else{
                //squares with no pieces
                if(i==0 || i ==7 || j==0 || j == 7)
                    set_empty(&board[i][j]);
                else{
                    //squares with red pieces
                    if((i%2 == 1 && (j < 3 || j> 4)) ||
                       (i%2 == 0 && (j == 3 || j==4)))
                        set_red(&board[i][j]);
                        //green squares
                    else set_green(&board[i][j]);
                }
            }
        }


    }


}

