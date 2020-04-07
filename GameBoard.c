//
// Created by Ruben van Breda on 2020/04/07.
//

#include "GameBoard.h"
#include <stdio.h>
#include <stdlib.h>


struct piece * push(color n_color,struct piece *top){
    piece *curr = top;
    top = malloc(sizeof(piece));
    top->p_color = n_color;
    top->next = curr;
    return top;
}
int get_stack_count(piece *n_stack){
    int count = 1;
    while(n_stack->next != NULL){
        count++;
        n_stack = n_stack->next;
    }

    return count;
}

