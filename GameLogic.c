//
// Created by Ruben van Breda on 2020/04/07.
//

#include "GameLogic.h"
#include "input_output.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


struct piece * push(color n_color,struct piece *top){
    piece *curr = top;
    top = malloc(sizeof(piece));
    top->p_color = n_color;
    top->next = curr;
    return top;
}


struct square * pushStack(struct square *n_square1, struct square *n_square2){
    // This function stacks top2 on top of stack top1
    //TODO: BUG Move 1 1 -> 2 1 . BOOM NO WORKY NO MORE

    int ns_size = get_stack_count(n_square1->stack) + get_stack_count(n_square2->stack); // new stack size
    piece *new_stackPtr = (piece *)malloc(sizeof(piece) * ns_size);
    piece *stack1 = (piece *)malloc(sizeof(piece)*get_stack_count(n_square1->stack));
    piece *stack2 = (piece *)malloc(sizeof(piece)*get_stack_count(n_square2->stack));

    stack1 = n_square1->stack;
    stack2 = n_square2->stack;


    //set the new_stackPtr = square1 stack
    new_stackPtr = n_square1->stack;
    piece *currentPiece = new_stackPtr;
    //loop through and assign the elements of stack1 to the variable new_stackPtr
    while (new_stackPtr->next != NULL){
        new_stackPtr = new_stackPtr->next;
    } //Move till the end of the pointer new_stackPtr

    new_stackPtr->next = stack2; //add the next pointer to point to secondStack

    //Place the new stack on the square
//    printStack(currentPiece, "currentStack ->");

    n_square2->stack = new_stackPtr;
    // '' This is needed to add the last piece of the stack to square2
    if(get_stack_count(n_square2->stack) < ns_size){
            n_square2->stack = push(currentPiece->p_color, n_square2->stack);
            printf("ADDED CURRENT PIECE\n");

    }

    //Emtpy the moved square, square1
    set_empty(n_square1);
    return n_square2;


}
int get_stack_count(piece *n_stack){
    //This function returns the amount of pieces in a stack n_stack
    int count = 0;
    while(n_stack != NULL){
        n_stack = n_stack->next;
        count++;

    }
//    //Check if there is a piece but next is null(count=0)
    if(n_stack!=NULL && n_stack->next == NULL){
        count++;
    }


    return count;
}

void MakeMove(struct square board[BOARD_SIZE][BOARD_SIZE],player n_player){
    bool isValidChoice = false; //checks that the player can move in a valid square
    Move move;
    // Get move
    int tempX,tempY,sc_result; //store temporary x,y values and sc_result to check if the input is correct
    while(isValidChoice == false){
        getchar();
        printf("%s, which square would you like to move: ",n_player.name);
        sc_result = scanf("%d %d",&tempX,&tempY);
        if(sc_result != 2){
            printf("invalid which square would you like to move: ",n_player.name);
            continue;
        }
        /* Check the a valid conditions and display the appropriate message if necessary*/
        if(tempX > BOARD_SIZE || tempX < 0 || tempY > BOARD_SIZE || tempY < 0){ printf("Move out of range,\n"); continue;}
        if(board[tempX][tempY].type == INVALID){ continue;}
        if(board[tempX][tempY].stack != NULL && board[tempX][tempY].stack->p_color != n_player.player_color){
            printf("Select a %s coloured square,\n",n_player.player_color?"green":"red");continue;}
        /* Valid condition */
        if(sc_result == 2 && board[tempX][tempY].type==VALID && board[tempX][tempY].stack->p_color == n_player.player_color){
            isValidChoice = true;
        }
    }
    move.x1 = tempX; move.y1 = tempY;

    // Where to move
    isValidChoice = false;
    while(isValidChoice == false){
        printf("%s, what square would you like to move to: ",n_player.name);
        sc_result = scanf("%d %d",&tempX,&tempY);
        if(sc_result != 2){
            printf("invalid which square would you like to move: ",n_player.name);
            continue;
        }
        /* Check the a valid conditions and display the appropriate message if necessary*/
        if(tempX > BOARD_SIZE || tempX < 0 || tempY > BOARD_SIZE || tempY < 0){ printf("Move out of range,\n"); continue;}
        if(board[tempX][tempY].type == INVALID){ continue;}
        /* Valid condition */
        if(sc_result == 2 && board[tempX][tempY].type==VALID){
            isValidChoice = true;
        }
    }
    move.x2 = tempX; move.y2 = tempY;

    int move_counts = get_stack_count(board[move.x1][move.y1].stack);


    /*  Preform the move */
    // Check stack not bigger than 5

    board[move.x2][move.y2] = *pushStack(&board[move.x1][move.y1],&board[move.x2][move.y2]);
//    printStack( board[move.x2][move.y2].stack, "new square");






//    board[move.x1][move.y1].type = INVALID;
    //TODO: Check that the player can move there
    //The square is a valid selection
//    if(board[move.x1][move.y1].stack->p_color == n_player.player_color){
//        int move_counts = get_stack_count(board[move.x1][move.y1].stack);
//        printf("Enter %d moves (u,d,l,r): ",move_counts);
//    }


}

