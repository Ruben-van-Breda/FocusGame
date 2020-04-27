//
// Created by Ruben van Breda on 2020/04/07.
//




#ifndef FOCUS_GAMELOGIC_H
#define FOCUS_GAMELOGIC_H
#endif //FOCUS_GAMELOGIC_H

#include <search.h>
#include <stdbool.h>
#include "input_output.h"
typedef struct Move{
    int x1,y1,x2,y2;
}Move;
//enum Action{
//    UP,DOWN,LEFT,RIGHT
//} Action;
//
//typedef struct Step{
//    enum Action action;
//    struct Step *next;
//}Step;







//functionality prototypes
int get_stack_count(piece *n_stack);
struct piece * push(color n_color,struct piece *top);
void fallenPieces(struct square *n_square1,player *p);
struct player playerUpdate(player *p, int own,int adv);
void testInFunc(struct player *p);
struct square * pushStack(struct square *n_square1, struct square *n_square2);

void MakeMove(struct square board[BOARD_SIZE][BOARD_SIZE],char *string,player *n_player,bool fromReserves);
int check_win(square board[BOARD_SIZE][BOARD_SIZE]);
int can_player_move(struct square board[BOARD_SIZE][BOARD_SIZE]);


struct Move ComputeDestination(struct square board[BOARD_SIZE][BOARD_SIZE],int *steps,Move n_move,int count);
Move GetValidMove(struct square board[BOARD_SIZE][BOARD_SIZE],player n_player,bool fromReserves);
Move GetValidDestination(struct square board[BOARD_SIZE][BOARD_SIZE],int *steps,Move n_move,int moves);
bool check_bounds(struct square board[BOARD_SIZE][BOARD_SIZE],Move move);

int myPrinter(const char *format,...);








