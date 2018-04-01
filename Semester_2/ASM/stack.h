#ifndef ASM_STACK_H
#define ASM_STACK_H

#include <stdlib.h>
#include <stdio.h>

/* Stack structure:
 *  Fields:
 *   elements -- array of int;
 *   size -- amount of ints already allocated
 *   busy -- amount of ints already used */

typedef struct {
    int *elements;
    int size;
    int busy;
} Stack;


/* Functions description:
 *  createStack -- creating stack pointer without allocating memory for ints
 *  clearStack -- clearing array and setting size and busy fields to default
 *  deleteStack -- free all memory used by stack
 *  pushStack -- push element to the top of stack. Reallocate memory if no free memory left
 *  popStack -- pop element from the top of stack */

Stack *createStack();

void clearStack(Stack *stack);

void deleteStack(Stack *stack);

void pushStack(Stack *stack, int element);

int popStack(Stack *stack);

#endif
