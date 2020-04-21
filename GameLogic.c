//
// Created by Ruben van Breda on 2020/04/07.
//

#include "GameLogic.h"
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

//    n_square2->stack = new_stackPtr;
    n_square2->stack = currentPiece;

    // '' This is needed to add the last piece of the stack to square2
//    if(get_stack_count(n_square2->stack) < ns_size){
//            printStack(n_square2->stack, "IN: n_square2->stack ->");
//        n_square2->stack = n_square2->stack->next;
//        printf("ADDED CURRENT PIECE\n");
//
//    }

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
        if (get_stack_count(board[tempX][tempY].stack) == 0) { continue; }
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

    int move_counts = get_stack_count(board[move.x1][move.y1].stack);
    Step *steps; //(Step*)malloc(move_counts*sizeof(Step));
    int actions[move_counts];
    if(steps==NULL){perror("Steps is null\n");}

    GetSteps(actions,move_counts);
    if(steps==NULL){perror("Steps is null\n");}

    move = ComputeDestination(board,actions,move,move_counts);


//    for (int i = 0; i < move_counts ; ++i) {
//        printf("step -> %d\n",steps->action);
//        steps =steps->next;
//    }

    // Where to move
    isValidChoice = false;
//    while (isValidChoice == false) {
//        printf("%s, what square would you like to move to: ", n_player.name);
//        sc_result = scanf("%d %d", &tempX, &tempY);
//        if (sc_result != 2) {
//            printf("Invalid which square would you like to move: ", n_player.name);
//            continue;
//        }
//        /* Check the a valid conditions and display the appropriate message if necessary*/
//        if (tempX > BOARD_SIZE || tempX < 0 || tempY > BOARD_SIZE || tempY < 0) {
//            printf("Move out of range,\n");
//            continue;
//        }
//        if (board[tempX][tempY].type == INVALID) { continue; }
//        /* Valid condition */
//        if (sc_result == 2 && board[tempX][tempY].type == VALID) {
//            isValidChoice = true;
//        }
//    }
//    move.x2 = tempX;
//    move.y2 = tempY;
    printStack(board[move.x2][move.y2].stack, "square2 : ");




    /*  Preform the move */
    board[move.x2][move.y2] = *pushStack(&board[move.x1][move.y1],&board[move.x2][move.y2]);
//    printStack(board[move.x2][move.y2].stack, "raw square");

    piece * fallenStack = malloc(sizeof(struct piece) * 5);
    fallenStack = fallenPieces(&board[move.x2][move.y2]);
    // add fallen stack to players reserves
    /*The fallen pieces can be : Kept(reserves)if(own), (own)Played(Place pieces on board any valid square), (other)destroy piece*/
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

//    free(steps);
}


struct piece *fallenPieces(struct square *n_square) {
    //printf("stack size = %d\n",get_stack_count(n_square->stack));
    if(get_stack_count(n_square->stack) <= STACK_LIMIT) return NULL;
    printStack(n_square->stack,"n_square ->");

    piece *tempStack = n_square->stack;
    piece * final_stack = malloc(sizeof(piece)*STACK_LIMIT);
    piece * new_stack = n_square->stack;
    int size = get_stack_count(n_square->stack);
    int count = 0;
    while(tempStack != NULL && count<STACK_LIMIT){
        tempStack = tempStack->next;
        count++;
    }
//    printStack(tempStack,"tempStack ->");
//    printStack(new_stack,"newStack bfr ->");

    for (int i = 0; i < count-1; ++i) {
        new_stack = new_stack->next;
    }
    new_stack->next = NULL;
//    printStack(new_stack,"newStack aft ->");

//    n_square->stack = new_stack;
//    printStack(n_square->stack,"out n_square ->");

    final_stack = tempStack;
//    printStack(final_stack,"FinalStack ->");
//    n_square->stack = NULL;
//    n_square->stack = final_stack;
    return final_stack;


}

Move GetValidMoves(){

}

struct Move ComputeDestination(struct square board[BOARD_SIZE][BOARD_SIZE],int *steps,Move n_move,int moves){
    int x = n_move.x1;
    int y = n_move.y1;
    bool isValid = false;
//    Step *temp = steps;
    while(isValid == false) {
//        steps = temp;
        if(steps==NULL){
            perror("steps null");
            n_move.x2 = 999;
            n_move.y2 = 999;
            return n_move;
            break;
        }
        int i = 0;
        int count = sizeof(steps)/ sizeof(steps[0]);
        while (i<moves) {
            if (*(steps+i)== UP) {
                x -= 1;
            }  if (*(steps+i) == DOWN) {
                x += 1;
            }  if (*(steps+i) == RIGHT) {
                y += 1;
            }  if (*(steps+i) == LEFT) {
                y -= 1;
            }
            i++;
        }

        n_move.x2 = x;
        n_move.y2 = y;

        if (check_bounds(board,n_move)) {
            isValid = true;
        }
    }
    return n_move;
}

bool check_bounds(struct square board[BOARD_SIZE][BOARD_SIZE],Move m){
    if (m.x2 > BOARD_SIZE || m.x2 < 0 || m.y2 > BOARD_SIZE || m.y2 < 0) {
        printf("Move out of range,\n");
        return false;
    }
    if(board[m.x2][m.y2].type == INVALID){
        return false;
    }

    return true;
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


