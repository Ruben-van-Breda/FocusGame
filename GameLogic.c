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

struct piece * pushStack(struct piece *stack1,struct piece *stack2){
    // This function stacks top2 on top of stack top1
    piece *curr_top1 = stack1;
    stack1 = malloc(sizeof(piece));

    //Find the last element of stack2
    while(stack1->next != NULL){
        stack1 = stack1->next;

    }
    stack1->next = stack2;
    curr_top1->next = stack2;

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

