
//
// Created by Lili on 24/03/2020.
//

#ifndef FOCUS_INPUT_OUTPUT_H
#define FOCUS_INPUT_OUTPUT_H
#include "game_init.h"
//#define clrscr() printf("\e[1;1H\e[2J")


enum Action{
    UP,DOWN,LEFT,RIGHT
} Action;

typedef struct Step{
    enum Action action;
    struct Step *next;
}Step;

#endif //FOCUS_INPUT_OUTPUT_H

//Function to print the board
void display_logo();
int display_instructions(square board[BOARD_SIZE][BOARD_SIZE],player n_player);
void print_board(square board[BOARD_SIZE][BOARD_SIZE]);
void printStack(struct piece *stack,char *string);
void GetSteps(int *steps,int count);
char ToLowerCase(char ch);
void clear_screen();
void ClearScreen();

int display_start_instructions(int type);




