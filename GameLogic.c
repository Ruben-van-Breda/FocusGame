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
    piece *new_stack = (piece *)malloc(sizeof(piece)*ns_size);
    piece *stack1 = (piece *)malloc(sizeof(piece)*get_stack_count(n_square1->stack));
    piece *stack2 = (piece *)malloc(sizeof(piece)*get_stack_count(n_square2->stack));

    stack1 = n_square1->stack;
    stack2 = n_square2->stack;


    //set the new_stack = square1 stack
    new_stack = n_square1->stack;
    piece *currentPiece = new_stack;
    printStack(new_stack,"new_stack ->");
    //loop through and assign the elements of stack1 to the variable new_stack
    while (new_stack->next != NULL){
        new_stack = new_stack->next;
    }
    printStack(new_stack,"new_stack loop stack1 ->");
    new_stack->next = stack2;
    new_stack = push(currentPiece->p_color,new_stack);
    printStack(new_stack,"new_stack loop stack12 ->");



//    new_stack = push(stack2->p_color,new_stack);

    printStack(new_stack,"new_stack ->");

    //Place the new stack on the square
    n_square2->stack = new_stack;
    printStack(n_square1->stack,"square ->");

    return n_square2;


}
/*struct square * pushStack(struct square *n_square1, struct square *n_square2){
    // This function stacks top2 on top of stack top1
    *//*piece *s1 = n_square1->stack;

    //Find the last element of n_square1
    if( s1 != NULL && s1->next == NULL){
        printf("\nget_stack_count == 1\n");
        s1->next = n_square2->stack;
        n_square1->stack = s1;
        return n_square1;
    }
    while(s1->next != NULL){
        s1 = s1->next;
    }
    s1->next = n_square2->stack;
    n_square1->stack->next = s1;
    //Remove all the pieces from the square2
    set_empty(n_square2);
    return n_square1;*//*

    int ns_size = get_stack_count(n_square1->stack) + get_stack_count(n_square2->stack); // new stack size
    piece *new_stack = (piece *)malloc(sizeof(piece)*ns_size);
    piece *stack1 = (piece *)malloc(sizeof(piece)*get_stack_count(n_square1->stack));
    piece *stack2 = (piece *)malloc(sizeof(piece)*get_stack_count(n_square2->stack));
//    n_square1->stack = (piece *)calloc(sizeof(piece),ns_size);
    stack1 = n_square1->stack;


    //set the new_stack = square2 stack
    new_stack = n_square2->stack;

    while (stack2->next != NULL){
        new_stack->next = stack2;
        printStack(stack2,"in \tt stack2 -> ");

        stack2 = stack2->next;
    }
    printStack(new_stack,"new_stack ->");


    while (stack1->next != NULL){
        new_stack = push(stack1->p_color,new_stack);
        printStack(new_stack,"in ns -> ");
        stack1 = stack1->next;
    }
    new_stack = push(stack1->p_color,new_stack);

    printStack(new_stack,"new_stack ->");

    n_square1->stack = new_stack;
    printStack(n_square1->stack,"square ->");

    return n_square1;


}*/
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

