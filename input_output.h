
//
// Created by Lili on 24/03/2020.
//

#ifndef FOCUS_INPUT_OUTPUT_H
#define FOCUS_INPUT_OUTPUT_H
#include "game_init.h"

#endif //FOCUS_INPUT_OUTPUT_H

//Function to print the board
void print_board(square board[BOARD_SIZE][BOARD_SIZE]);
void printStack(struct piece *stack,char *string);
int display_instructions(int type);
void MakeMove(struct square board[BOARD_SIZE][BOARD_SIZE],player n_player);




