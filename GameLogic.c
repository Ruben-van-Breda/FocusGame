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

struct square * pushStack(struct square *stack1,struct square *stack2){
    // This function stacks top2 on top of stack top1
    piece *s1 = stack1->stack;
    stack1->stack = malloc(sizeof(struct piece));

    //Find the last element of stack1
    if( s1 != NULL && s1->next == NULL){
        printf("\nget_stack_count == 1\n");
        s1->next = stack2->stack;
        stack1->stack = s1;
        return stack1;
    }
    while(s1->next != NULL){
        s1 = s1->next;
    }
    s1->next = stack2->stack;
    stack1->stack->next = s1;
    //Remove all the pieces from the square2
    set_empty(stack2);
    return stack1;


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

