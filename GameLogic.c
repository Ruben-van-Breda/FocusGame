//
// Created by Ruben van Breda on 2020/04/07.
//

#include "GameLogic.h"
#include "input_output.h"
#include <stdio.h>
#include <stdlib.h>


struct piece * push(color n_color,struct piece *top){
    piece *curr = top;
    top = malloc(sizeof(piece));
    top->p_color = n_color;
    top->next = curr;
    return top;
}


struct square * pushStack(struct square *n_square1, struct square *n_square2){
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
//    printStack(new_stackPtr, "new_stackPtr ->");
//
    //loop through and assign the elements of stack1 to the variable new_stackPtr
    while (new_stackPtr->next != NULL){
        new_stackPtr = new_stackPtr->next;
    } //Move till the end of the pointer new_stackPtr

    new_stackPtr->next = stack2; //add the next pointer to point to secondStack

    //Place the new stack on the square
    n_square2->stack = currentPiece;
    // '' This is needed to add the last piece of the stack to square2
    n_square2->stack = push(currentPiece->p_color, n_square2->stack);

    //Emtpy the moved square, square1
    set_empty(n_square1);
    return n_square2;


}
int get_stack_count(piece *n_stack){
    //This function returns the amount of pieces in a stack n_stack
    int count = 1;
    while(n_stack->next != NULL){
        n_stack = n_stack->next;
        count++;

    }
//    //Check if there is a piece but next is null(count=0)
//    if(n_stack!=NULL && count==0){
//        count++;
//    }


    return count;
}

