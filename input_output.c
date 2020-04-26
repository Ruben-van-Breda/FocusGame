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
 * Valid squares with a BLUE piece are printed as | G |
 * Valid squares with a RED piece are printed as | R | */

void print_board(square board[BOARD_SIZE][BOARD_SIZE]){
    wchar_t empty_square = 0x25A2;
    wchar_t invalid_square = 0x25A6;
    wchar_t ui_player1 = UI_PLAYER1_CODE;
    wchar_t ui_player2 = UI_PLAYER2_CODE;
    wchar_t ui_test = 0x20DD;//0x25EF;//0x26AB;//0x274D;//0x26AA; //0x20DD;
    ui_player1 = 0x1F535;

    printf("*********** The Board ***********\n");
    printf("\t0\t1\t2\t3\t4\t5\t6\t7\n");
    for(int i = 0; i < BOARD_SIZE; i ++){
        printf("%d\t",i);

        for (int j = 0; j < BOARD_SIZE; j++){
            if(board[i][j].type == VALID) {
                if(board[i][j].stack == NULL){
//                    printf("[ ");
                    wprintf(L"%lc\t", empty_square);}
                else{
                    if (board[i][j].stack->p_color == BLUE){
                         wprintf(ANSI_COLOR_BLUE L"%lc%d%s\t", UI_BLUE_CIRCLE, get_stack_count(board[i][j].stack),ANSI_COLOR_RESET);}

                    else {
                         wprintf(ANSI_COLOR_RED L"%lc%d%s\t", UI_RED_CIRCLE,get_stack_count(board[i][j].stack),ANSI_COLOR_RESET);}
                }
            }
            else
                wprintf(L"%lc\t", invalid_square);
        }
    printf("\n");
    }
}

void printStack(struct piece *stack,char *string){
    printf("%s ",string);

    while(stack != NULL){
        printf("%s",stack->p_color?"B":"R");
        stack = stack->next;
    }

    printf("\n");

}

void GetSteps(int *steps,int count) {
    /*  This function will get the steps from the player and store it in the param n_steps
            */

    for (int j = 0; j < count; ++j) { steps[j] = -1;} //Initialise the array with null -> -1

    bool isValid = false;
    while(isValid == false){
        char input[count];
        char c;
        printf("Please enter %d moves (up, down, left, right)\n", count);
        printf("Moves: ");
        scanf("%s",input);

        //loop through input and convert to steps
        int i = 0;
        for ( i = 0;i < count; ++i) {
            c = input[i];
            c = ToLowerCase(c);
            if((c == 'u') || (c=='d') || (c=='r') || (c== 'l')){
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
                        *(steps+i) = RIGHT;
                        break;
                    default:
                        printf("GetSteps DEFUALT");
                        *(steps+i) = 99;
                }
            }
            else{
                printf("Invalid input [u,d,l,r] ");
                break;
            }

        }
        if(i==count){
            isValid = true;
        }
    }



}

int display_start_instructions(int type){
    int choice = -1;
    bool playGame = false;
    while(playGame == false){
        printf(ANSI_COLOR_MAGENTA"\n___ Instructions ___\n");
        printf("1) Start Game\n");
        printf("2) How to play\n");
        printf("3) About Game%s\ninput: ",ANSI_COLOR_RESET);
        scanf("%d",&choice);
        switch(choice){
            case 1:
                playGame = true;
                break;
            case 2:
                printf(ANSI_COLOR_CYAN "Domination/Focus Board Game\n"
                       "First to choose a square you would like to move enter the coordinates of the square such as (1 1) for the square at row 1 column 1\n"
                       "Once a valid square is selected you will have a number of moves (up, down, left and right) \ndepending on the stack of the selected square. "
                       "Moving up and right will be : ur\n"
                       "If a stack reaches 5 the pieces will fall from the bottom, fallen Stack. If the fallen pieces belong to you it will be added for later in the game, \n"
                       "if the piece is not one of your own, it will be added to your adversary.\n"
                       "If you have no pieces left on the board nor any pieces of your own captured the other player wins.%s",ANSI_COLOR_RESET);
                break;
            case 3:
                printf(ANSI_COLOR_YELLOW"About Focus Project, this project was written by Ruben van Breda in C for first year semester 2.%s\n",ANSI_COLOR_RESET);
                break;
        }
    }





    return 0;
}

int display_instructions(square board[BOARD_SIZE][BOARD_SIZE],player n_player){
    wprintf(L"%s %lc you own %d pieces\n",n_player.name,n_player.player_color?UI_BLUE_CIRCLE:UI_RED_CIRCLE,n_player.own_pieces);

    int choice = -1;
    while(choice != 1 && choice!= 2){
        printf("0) View the stack of a square\n");
        if(n_player.own_pieces > 0){
            printf("1) Move piece on board\n");
            printf("2) Play a piece on the board from reserves\n");
        }
        else if(n_player.own_pieces <= 0){
//            return 1;
            printf("1) Move piece on board\n");
        }

        scanf("%d",&choice);
        /* Print out a stack on a board */
        if(choice == 0){
            printf("Enter which square you would like to view: ");

            Move m = GetValidMove(board,n_player,true);
            printf("[%d][%d] -> ",m.x1,m.y1);
            printStack(board[m.x1][m.y1].stack,"");
        }

        if(n_player.own_pieces <= 0 && choice == 2)
        {
            choice = -1;
        }




    }
    return choice;


}

void display_logo(){
    printf(ANSI_COLOR_BLUE "\n____________________________________________\n");
    printf("%s******\t%s****\t %s****\t %s*****\t %s******\n",ANSI_COLOR_BLUE,ANSI_COLOR_RED,ANSI_COLOR_BLUE,ANSI_COLOR_RED,ANSI_COLOR_BLUE);
    printf("%s*   \t%s*  *\t %s*     \t%s*    \t%s*     \n",ANSI_COLOR_BLUE,ANSI_COLOR_RED,ANSI_COLOR_BLUE,ANSI_COLOR_RED,ANSI_COLOR_BLUE);
    printf("%s***** \t%s*  *\t %s*   \t %s*****\t %s****  \n",ANSI_COLOR_BLUE,ANSI_COLOR_RED,ANSI_COLOR_BLUE,ANSI_COLOR_RED,ANSI_COLOR_BLUE);
    printf("%s*     \t%s*  *\t %s*   \t     %s*\t %s*  \n",ANSI_COLOR_BLUE,ANSI_COLOR_RED,ANSI_COLOR_BLUE,ANSI_COLOR_RED,ANSI_COLOR_BLUE);
    printf("%s*     \t%s****\t %s****\t %s*****\t %s******\n",ANSI_COLOR_BLUE,ANSI_COLOR_RED,ANSI_COLOR_BLUE,ANSI_COLOR_RED,ANSI_COLOR_BLUE);
    printf("____________________________________________ by Ruben van Breda %s\n",ANSI_COLOR_RESET);





}

void clear_screen(){
//int c;
//while((c=getchar()) != '\n' && c != ' ' && c != '\t' && c !=  EOF);
//fflush(stdin);
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
#endif

#if defined(_WIN32) || defined(_WIN64)
        system("cls");
#endif

}
char ToLowerCase(char ch){
    //  Checks if the character is in UpperCase
    if(ch >= 65 && ch<=90){
        ch += 32; // Change character to lowercase
    }

    return ch;
}







