//
// Created by Ruben van Breda on 2020/04/07.
//

#include "GameLogic.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <wchar.h>


//square board[BOARD_SIZE][BOARD_SIZE];

struct piece *push(color n_color, struct piece *top) {
    piece *curr = top;
    top = malloc(sizeof(piece));
    top->p_color = n_color;
    top->next = curr;
    return top;
}
struct square *pushStack(struct square *n_square1, struct square *n_square2) {
    // This function stacks top2 on top of stack top1
    if(n_square1==n_square2){return n_square1;}

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

void MakeMove(struct square board[BOARD_SIZE][BOARD_SIZE],char *string,player *n_player,bool fromReserves) {
    /*  This function handles the logic to preform a move from a user per turn
     * */
    printf("%s",n_player->player_color?ANSI_COLOR_BLUE:ANSI_COLOR_RED); //set console color

    bool isValidChoice = false; //checks that the player can move in a valid square

    if(fromReserves){
        printf("Playing from reserves\n");
        wprintf(L"%s %lc, which square would you like to place your piece: ",n_player->name,n_player->player_color?UI_BLUE_CIRCLE:UI_RED_CIRCLE);
        Move move = GetValidMove(board,*n_player,fromReserves);
        /*  Preform Move    */
        board[move.x1][move.y1].stack = push(n_player->player_color, board[move.x1][move.y1].stack);
        fallenPieces(&board[move.x1][move.y1],&n_player);
        return;
    }
    /*  prompt player to enter a square */
    wprintf(L"%s %lc, which square would you like to move: ",n_player->name,n_player->player_color?UI_BLUE_CIRCLE:UI_RED_CIRCLE);
    /* get a valid move from user   */
    Move move = GetValidMove(board,*n_player,fromReserves);
    printf("[%d][%d] -> ",move.x1,move.y1); // display square to player
    printStack(board[move.x1][move.y1].stack, "");

    /* Get steps from user */
    int move_counts = get_stack_count(board[move.x1][move.y1].stack);
    int actions[move_counts];
    GetSteps(actions,move_counts);

    /* Compute the destination of square 2 */
    move = GetValidDestination(board,actions,move,move_counts);
    printf("[%d][%d] -> ",move.x2,move.y2);
    printStack(board[move.x2][move.y2].stack, "");

    /*  Preform the move */
    board[move.x2][move.y2] = *pushStack(&board[move.x1][move.y1],&board[move.x2][move.y2]);
    fallenPieces(&board[move.x2][move.y2],n_player);
}


void fallenPieces(struct square *n_square, player *n_player) {
    /*This function takes in a square and removes pieces from the bottom of the stack exceeding the STACK_LIMIT
     Then the new stack of fallen pieces are counted and allocated towards the players own_pieces and adversary members.
     */

    if(get_stack_count(n_square->stack) <= STACK_LIMIT) return ;
    printStack(n_square->stack,"new square ->");

    piece *tempStack = n_square->stack;
    piece * final_stack = malloc(sizeof(piece)*STACK_LIMIT);
    piece * new_stack = n_square->stack;
    int count = 0;
    while(tempStack != NULL && count<STACK_LIMIT){
        tempStack = tempStack->next;
        count++;
    }
    for (int i = 0; i < count-1; ++i) {
        new_stack = new_stack->next;
    }
    //square is now with in LIMIT
    new_stack->next = NULL; // set the next pointer of n_square to null

    /* assign the final stack the limited stack tempStack of n_square */
    final_stack = tempStack;
    tempStack = final_stack; // assign temp to allow to iterate over the stack to check pieces

     /* add the fallen pieces to own_pieces and adversary*/
    if(tempStack!=NULL){
        int my_pieces = n_player->own_pieces;
        int others = n_player->adversary;
        while (tempStack!=NULL){
            if(tempStack->p_color == n_player->player_color){ my_pieces +=1;} // if its my own piece
            else{ others += 1;} // not my piece
            tempStack = tempStack->next;
        }
        /*  assign player values    */
        n_player->own_pieces = my_pieces;
        n_player->adversary = others;
    }
    if(final_stack != NULL){
        printStack(final_stack, "Fallen Stack ->");
    }


}

Move GetValidMove(struct square board[BOARD_SIZE][BOARD_SIZE],player n_player,bool fromReserves){
    /*  This function will prompt the user to enter a valid row and column values on a board
     * depending on the param fromReserves which will allow a pos which is empty or not of their color
     * */
    printf("%s",ANSI_COLOR_RESET); // reset the console color

    bool isValidChoice = false; // this will keep track if a valid choice has been made
    int tempX, tempY; // the temporary values for x and y
    Move move; // The players move
    while (isValidChoice == false) {
        getchar();
        /*  Get input from player   */
        int sc_result = scanf("%d %d", &tempX, &tempY);
        /* 2 correct values were not entered */
        if(sc_result!=2){
            //Print error to player
            printf("%sInvalid input. %s\n",ANSI_COLOR_ERROR,ANSI_COLOR_RESET);
            continue;
        }
        /*  Set move values */
        move.x1 = tempX; move.x2 = move.x1;
        move.y1 = tempY; move.y2 = move.y1;

        /*  Validation  */
        bool isEmpty = get_stack_count(board[tempX][tempY].stack) == 0;
        bool isSameColor = board[tempX][tempY].stack != NULL && board[tempX][tempY].stack->p_color == n_player.player_color;
        /* Invalid conditions */
        if(!check_bounds(board,move)){ continue;}; // outside of bounds
        if (isEmpty && !fromReserves) { continue; } // empty and not from reserves
        if (!isSameColor && !fromReserves) {
            //Print error to user with coloring of erro
            printf("%sSelect a %s coloured square%s\n",ANSI_COLOR_ERROR, n_player.player_color ? "blue" : "red",ANSI_COLOR_RESET);
            continue;
        }
        /* Valid conditions */
        else if(isEmpty && fromReserves){isValidChoice = true; break;}
        if(isSameColor && fromReserves){isValidChoice = true; break;}
        if(sc_result == 2 && board[tempX][tempY].type == VALID && fromReserves){ isValidChoice = true; break;}
        else if (sc_result == 2 && board[tempX][tempY].type == VALID &&
            board[tempX][tempY].stack->p_color == n_player.player_color) {
            isValidChoice = true;
        }
    }//@END while
    return move;
}
Move GetValidDestination(struct square board[BOARD_SIZE][BOARD_SIZE],int *steps,Move n_move,int moves){
    /*  This function will insure a valid  move is returned if the steps are valid  */
    Move temp = n_move;
    temp = ComputeDestination(board,steps,temp,moves);
    while(temp.x1 == 99){ // 99 is to act as a NULL indicator
        GetSteps(steps,moves);
        temp = ComputeDestination(board,steps,n_move,moves);
    }
    return temp;
}

struct Move ComputeDestination(struct square board[BOARD_SIZE][BOARD_SIZE],int *steps,Move n_move,int moves){
    /*This function takes in a move with x1 and y1 assigned and a array of steps as param.
     * It will compute the transformation of square1 by applying the steps
     * the function will validate that the destination square is a in bounds */
    Move temp = n_move;
    int x = temp.x1;
    int y = temp.y1;
    int i = 0;
    /* compute the destination coordinates */
    while (i<moves) {
        if (*(steps+i)== UP) {
            x -= 1;
        } if (*(steps+i) == DOWN) {
            x += 1;
        } if (*(steps+i) == RIGHT) {
            y += 1;
        } if (*(steps+i) == LEFT) {
            y -= 1;
        }
        i++;
    }
    /*  Assign values for x2 and y2 */
    n_move.x2 = x;
    n_move.y2 = y;
    // if the move is out of bounds
    if (!check_bounds(board,n_move)) {
        temp.x1 = 99; // set a null indicator
        return temp;
    }
    return n_move; // valid move

}

bool check_bounds(struct square board[BOARD_SIZE][BOARD_SIZE],Move m){
    /*  Manage validation of coordinates */
    if (m.x1 >= BOARD_SIZE || m.x1 < 0 || m.y1 >= BOARD_SIZE || m.y1 < 0) {
        printf("%sMove out of range,%s\n",ANSI_COLOR_ERROR,ANSI_COLOR_RESET);
        return false;
    }

    if (m.x2 >= BOARD_SIZE || m.x2 < 0 || m.y2 >= BOARD_SIZE || m.y2 < 0) {
        printf("%sMove out of range,%s\n",ANSI_COLOR_ERROR,ANSI_COLOR_RESET);
        return false;
    }
    if(board[m.x1][m.y1].type == INVALID||board[m.x2][m.y2].type == INVALID){
        printf("%sInvalid square%s\n",ANSI_COLOR_ERROR,ANSI_COLOR_RESET);
        return false;
    }
    /*  is valid position   */
    return true;
}

int can_player_move(struct square board[BOARD_SIZE][BOARD_SIZE]){
    /*
     *
     * */

    //  Counts the amount of pieces for each player on the board
    int player_counter[PLAYERS_NUM];
    //  Initialise the player frequency to all zero values
    for (int k = 0; k < PLAYERS_NUM; ++k) {player_counter[k] = 0;}
    /*  Add up player pieces on board   */
    for(int i = 0; i < BOARD_SIZE; i ++){
        for (int j = 0; j < BOARD_SIZE; j++){
            //Check that the square is valid and that the stack is not null
            if(board[i][j].type == VALID && board[i][j].stack != NULL ) {
                color top = board[i][j].stack->p_color; //top color
                switch (top){
                    case RED:
                        player_counter[RED]++; // increase the counter for the appropriate player
                        break;
                    case BLUE:
                        player_counter[BLUE]++;// increase the counter for the appropriate player
                        break;
                }
            }
        }
    }
    // Print info to players
    wprintf(L"\n-----%d %lc, %d %lc-----\n",player_counter[0],UI_RED_CIRCLE,player_counter[1],UI_BLUE_CIRCLE);
    bool playerCanMove = true; // checks if there is a player that can move
    /*  Loop through the players frequency array    */
    for (int l = 0; l < PLAYERS_NUM; ++l) {
        playerCanMove = (player_counter[l] > 0); // if the player has pieces on the board
        if(playerCanMove == false){ return l; } // if the player doesnt have any pieces, return the index of the loser
    }
    return -1; //play on, no issues
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


