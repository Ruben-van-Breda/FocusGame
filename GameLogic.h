//
// Created by Ruben van Breda on 2020/04/07.
//




#ifndef FOCUS_GAMELOGIC_H
#define FOCUS_GAMELOGIC_H
#endif //FOCUS_GAMELOGIC_H

#include "input_output.h"

//functionality prototypes
int get_stack_count(piece *n_stack);
struct piece * push(color n_color,struct piece *top);
struct piece * pushStack(struct piece *top1,struct piece *top2);




