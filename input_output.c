//
// Created by Lili on 26/03/2020.
//

//
// Created by Lili on 24/03/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include "input_output.h"
#include "GameLogic.h"


#define UI_BLACK_SQAURE 0x25A0;
#define UI_INVALID_SQAURE 0x25A7;



/* Function to print the board:
 * Invalid Squares are printed as | - |
 * Valid empty squares are printed as |   |
 * Valid squares with a GREEN piece are printed as | G |
 * Valid squares with a RED piece are printed as | R | */

void print_board(square board[BOARD_SIZE][BOARD_SIZE]){
    wchar_t empty_square = 0x25A2;
    wchar_t invalid_square = 0x25A6;
    wchar_t ui_player1 = UI_PLAYER1_CODE;
    wchar_t black_square = UI_PLAYER2_CODE;

    printf("\t****** The Board ******\n");
    printf("\t0\t1\t2\t3\t4\t5\t6\t7\n");
    for(int i = 0; i < BOARD_SIZE; i ++){
        printf("%d\t",i);

        for (int j = 0; j < BOARD_SIZE; j++){
            if(board[i][j].type == VALID) {
                if(board[i][j].stack == NULL){//printf("|   ");
//                    printf("[ ");
                    wprintf(L"%lc\t", empty_square);}
                else{
                    if (board[i][j].stack->p_color == GREEN){//printf("| G%d",get_stack_count(board[i][j].stack));
                         wprintf(ANSI_COLOR_GREEN L"%lc%d%s\t", ui_player1, get_stack_count(board[i][j].stack),ANSI_COLOR_RESET);}

                    else {//printf("| R%d",get_stack_count(board[i][j].stack));
                         wprintf(ANSI_COLOR_RED L"%lc%d%s\t", black_square,get_stack_count(board[i][j].stack),ANSI_COLOR_RESET);}
                }
            }
            else
//                printf("| - ");
                wprintf(L"%lc\t", invalid_square);
        }
//        printf("|\n");
    printf("\n");
    }
}

void printStack(struct piece *stack,char *string){
    printf("%s ",string);

//    //There is only one piece in the stack
//    if(stack!=NULL && stack->next == NULL){
//        printf("%d\n",stack->p_color);
//        return;
//    }

    while(stack != NULL){
        printf("%d",stack->p_color);
        stack = stack->next;
    }
//    printf("%d",stack->p_color);

    printf("\n");

}

void GetSteps(int *steps,int count) {
    /*  This function will get the steps from the player and store it in the param n_steps
            */

    for (int j = 0; j < count; ++j) { steps[j] = -1;} //Initialise the array with null -> -1


    char input[count];
    printf("Please enter %d moves \n(up, down, left, right)\n", count);
    printf("Moves: ");
    scanf("%s",&input);
    //loop through input and convert to steps
    for (int i = 0; i < count; ++i) {
        char c = input[i];
        //TODO: EDGE CASES, VALIDATION

        switch (c) {
            case 'u':
                *(steps+i) = UP;
                break;
            case 'd':
                *(steps+i) = DOWN;
                break;
            case 'l':
                *(steps+i) = LEFT;
                break;
            case 'r':
//                temp_steps->action = RIGHT;
                *(steps+i) = RIGHT;
                break;
            default:
                printf("GetSteps DEFUALT");
                *(steps+i) = 99;
        }
    }
}




int display_instructions(int type){
    printf("\n___ Instructions ___\n");
    switch(type){
        case 0: // What square would the player like to move

            //TODO: Get the square which must be moved
           // printf("What square would you like to move?\n");

            //TODO: CHeck that the square can be moved by the player
            //TODO: Get the move_count
            //TODO: Get the user move





            break;
        default:
            printf("What would you like to do ******  ?");
            break;
    }
    return 0;
}






