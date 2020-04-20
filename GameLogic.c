//
// Created by Ruben van Breda on 2020/04/07.
//

#include "GameLogic.h"
#include "input_output.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>


struct piece *push(color n_color, struct piece *top) {
    piece *curr = top;
    top = malloc(sizeof(piece));
    top->p_color = n_color;
    top->next = curr;
    return top;
}


struct square *pushStack(struct square *n_square1, struct square *n_square2) {
    // This function stacks top2 on top of stack top1
    //TODO: BUG Move 1 1 -> 2 1 . BOOM NO WORKY NO MORE

    int ns_size = get_stack_count(n_square1->stack) + get_stack_count(n_square2->stack); // new stack size
    piece *stack1 = n_square1->stack;
    piece *stack2 = n_square2->stack;

//    printStack(n_square1, "square1 ->");
//    printStack(n_square2, "square2 ->");

    //set the new_stackPtr = square1 stack
    piece *new_stackPtr = n_square1->stack;
    piece *currentPiece = new_stackPtr;
    //loop through and assign the elements of stack1 to the variable new_stackPtr
    while (new_stackPtr->next != NULL) {
        new_stackPtr = new_stackPtr->next;
    } //Move till the end of the pointer new_stackPtr

    new_stackPtr->next = stack2; //add the next pointer to point to secondStack

    //Place the new stack on the square

    n_square2->stack = new_stackPtr;
    // '' This is needed to add the last piece of the stack to square2
    if (get_stack_count(n_square2->stack) < ns_size) {
        n_square2->stack = push(currentPiece->p_color, n_square2->stack);
        printf("ADDED CURRENT PIECE\n");

    }
//    printStack(n_square2->stack, "currentStack ->");


    //Emtpy the moved square, square1
    set_empty(n_square1);
    return n_square2;


}

int get_stack_count(piece *n_stack) {
    //This function returns the amount of pieces in a stack n_stack
    int count = 0;
    while (n_stack != NULL) {
        n_stack = n_stack->next;
        count++;

    }
//    //Check if there is a piece but next is null(count=0)
    if (n_stack != NULL && n_stack->next == NULL) {
        count++;
    }


    return count;
}

void MakeMove(struct square board[BOARD_SIZE][BOARD_SIZE], player n_player) {
    bool isValidChoice = false; //checks that the player can move in a valid square
    Move move;
    // Get move
    int tempX, tempY, sc_result; //store temporary x,y values and sc_result to check if the input is correct

    while (isValidChoice == false) {
        getchar();
        printf("%s, which square would you like to move: ", n_player.name);
        sc_result = scanf("%d %d", &tempX, &tempY);
        if (sc_result != 2) {
            printf("Invalid which square would you like to move: ", n_player.name);
            continue;
        }
        /* Check the a valid conditions and display the appropriate message if necessary*/
        if (tempX > BOARD_SIZE || tempX < 0 || tempY > BOARD_SIZE || tempY < 0) {
            printf("Move out of range,\n");
            continue;
        }
        if (board[tempX][tempY].type == INVALID) { continue; }
        if (board[tempX][tempY].stack != NULL && board[tempX][tempY].stack->p_color != n_player.player_color) {
            printf("Select a %s coloured square,\n", n_player.player_color ? "green" : "red");
            continue;
        }
        /* Valid condition */
        if (sc_result == 2 && board[tempX][tempY].type == VALID &&
            board[tempX][tempY].stack->p_color == n_player.player_color) {
            isValidChoice = true;
        }
    }
    // end, which square would you like to move:
    move.x1 = tempX;
    move.y1 = tempY;
    piece *square1Stack = board[move.x1][move.y1].stack;
    printStack(square1Stack, "square1 : ");

    // Where to move
    isValidChoice = false;
    while (isValidChoice == false) {
        printf("%s, what square would you like to move to: ", n_player.name);
        sc_result = scanf("%d %d", &tempX, &tempY);
        if (sc_result != 2) {
            printf("Invalid which square would you like to move: ", n_player.name);
            continue;
        }
        /* Check the a valid conditions and display the appropriate message if necessary*/
        if (tempX > BOARD_SIZE || tempX < 0 || tempY > BOARD_SIZE || tempY < 0) {
            printf("Move out of range,\n");
            continue;
        }
        if (board[tempX][tempY].type == INVALID) { continue; }
        /* Valid condition */
        if (sc_result == 2 && board[tempX][tempY].type == VALID) {
            isValidChoice = true;
        }
    }
    move.x2 = tempX;
    move.y2 = tempY;

    int move_counts = get_stack_count(board[move.x1][move.y1].stack);


    /*  Preform the move */
    board[move.x2][move.y2] = *pushStack(&board[move.x1][move.y1],&board[move.x2][move.y2]);
    piece * fallenStack = malloc(sizeof(struct piece) * 5);
    fallenStack = fallenPieces(&board[move.x2][move.y2]);
    printStack(fallenStack, "Fallen Stack ->");
    printStack(board[move.x2][move.y2].stack, "new square");

    //TODO: LOGIC FOR FALLEN PIECES OF A STACK
//   FallenPieces(board[move.x2][move.y2].stack);










//    board[move.x1][move.y1].type = INVALID;
    //TODO: Check that the player can move there
    //The square is a valid selection
//    if(board[move.x1][move.y1].stack->p_color == n_player.player_color){
//        int move_counts = get_stack_count(board[move.x1][move.y1].stack);
//        printf("Enter %d moves (u,d,l,r): ",move_counts);
//    }


}

//struct square *fallenPieces(struct square *n_square1, struct square *n_square2) {
//
////    int stack1_size = get_stack_count(n_square1->stack);
////    int stack2_size = get_stack_count(n_square2->stack);
////    int total_size = stack1_size + stack2_size;
////
//////    myPrinter("sd","stack1 size",stack1_size);
////
////
////    if (total_size > STACK_LIMIT) {
////        printf("\nLOGIC FOR FALLEN PIECES OF A STACK\n");
////
////
////        //Delta is the difference between the new stack and the stack limit
////        int delta = stack1_size - STACK_LIMIT;
////        piece *fallenStack = (piece *) malloc(sizeof(piece) * total_size -
////                                              STACK_LIMIT); //Allocate memory for the fallen pieces (excess > stack_limit)
////        piece *new_stackPtr = (piece *) malloc(sizeof(piece) * total_size);
////        new_stackPtr = n_square1->stack;
////
////        int count = 0;
////        if (total_size > STACK_LIMIT) {
////            while (count < STACK_LIMIT && new_stackPtr->next != NULL) {
////                new_stackPtr = new_stackPtr->next;
////                count++;
////            } // at end of stack1 or count == limit
////            if (count == STACK_LIMIT) {
////                printf("Return ");
////                printStack(n_square1, "square 1 as its reached the max size");
////                return n_square1;
////            }
////
////            printf("Count after 1st loop = %d\n", count);
//////            printStack(new_stackPtr,"1currentStack ->");
////
////            new_stackPtr->next = n_square2->stack;
////            printStack(new_stackPtr, "2currentStack ->");
////
////            while (count < STACK_LIMIT && new_stackPtr->next != NULL) {
////                new_stackPtr = new_stackPtr->next;
////                count++;
////            }  // at end of stack2 or count == limit
////            printf("END COUNT == %d\n", count);
////            printf("Excess of %d\n", total_size - count);
////            int excess = total_size - count;
////            if (excess <= 0) {
////                //Then there is no excess
////                fallenStack = NULL;
////                n_square2->stack = new_stackPtr;
////                return n_square2;
////
////            } else if (excess > 0) {
////                printStack(new_stackPtr,"newStackPtr->");
////                n_square2->stack = new_stackPtr;
////                fallenStack = new_stackPtr;
////                printStack( fallenStack,"fallenStack -> ");
//////                new_stackPtr->next = NULL;
////                return n_square2;
////            }
////
////            printStack(new_stackPtr, "3currentStack ->");
////
////
////            if (n_square2->stack != NULL) {
////                fallenStack = n_square2->stack;
////            }
////            printStack("fallenStack->", fallenStack);
////
////        }
////    } else {
////        n_square2 = pushStack(n_square1, n_square2);
////        return n_square2;
////    }
//
//
//}
struct piece *fallenPieces(struct square *n_square) {
    printf("stack size = %d\n",get_stack_count(n_square->stack));
    if(get_stack_count(n_square->stack) <= STACK_LIMIT) return NULL;
    printStack(n_square->stack,"n_square ->");

    piece *tempStack = n_square->stack;
    piece * final_stack = malloc(sizeof(piece)*STACK_LIMIT);
    int size = get_stack_count(n_square->stack);
    int count = 0;
    while(tempStack != NULL && count<STACK_LIMIT){
        tempStack = tempStack->next;
        count++;
    }
    for (int i = 0; i < count; ++i) {
        n_square->stack = n_square->stack->next;
    }

    final_stack = tempStack;
    printStack(final_stack,"FinalStack ->");
//    n_square->stack = NULL;
//    n_square->stack = final_stack;
    return final_stack;


}

int myPrinter(const char *format, ...) {
    //Takes in a string of arguments and prints the arguments accroding to their type given in the string
    va_list args;
    int count;
    /* initialize ap for num number of arguments */
    va_start(args, format);
    char c; // Declare a char var if a char is an argument.

    while (*format != '\0') {
        switch (*format++) {
            case 's':
                fprintf(stdout, "%s\n", va_arg(args, const char *));
                break;
            case 'c':
                c = (char) va_arg(args, int);
                printf("%c\n", c);
                // fprintf(stdout, "%c\n", count, c);
                break;
            case 'd':
                fprintf(stdout, "%d\n", va_arg(args, int));
                break;
            case 'f':
                fprintf(stdout, "%f\n", va_arg(args, double));
                break;
        }
    }
    va_end(args);
    return 0;
}


