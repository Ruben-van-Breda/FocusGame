//
// Created by Lili on 26/03/2020.
//

//
// Created by Lili on 24/03/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include "input_output.h"
#include "GameLogic.h"


/* FUnction to print the board:
 * Invalid Squares are printed as | - |
 * Valid empty squares are printed as |   |
 * Valid squares with a GREEN piece are printed as | G |
 * Valid squares with a RED piece are printed as | R | */

void print_board(square board[BOARD_SIZE][BOARD_SIZE]){
    printf("****** The Board ******\n");
    for(int i = 0; i < BOARD_SIZE; i ++){
        for (int j = 0; j < BOARD_SIZE; j++){
            if(board[i][j].type == VALID) {
                if(board[i][j].stack == NULL)
                    printf("|   ");
                else{
                    if (board[i][j].stack->p_color == GREEN)
                        printf("| G%d",get_stack_count(board[i][j].stack));
                    else printf("| R%d",get_stack_count(board[i][j].stack));
                }
            }
            else
                printf("| - ");
        }
        printf("|\n");
    }
}

void printStack(struct piece *stack){
    printf("Stack -> ");

    //There is only one piece in the stack
    if(stack!=NULL && stack->next == NULL){
        printf("%d",stack->p_color);
    }

    while(stack->next != NULL){
        printf("%d",stack->p_color);
        stack = stack->next;
    }

    printf("\n");

}




