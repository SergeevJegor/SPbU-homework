#include "stack.h"

#define INITIAL_STACK_SIZE 8
#define SIZE_MULTIPLIER 2

Stack *createStack() {
    Stack *stack;
    stack = (Stack *) calloc(1, sizeof(Stack));
    if (!stack) {
        printf("ERROR: Cannot allocate memory for stack");
        exit(1); // TODO invent error number
    }
    return stack;
}

void clearStack(Stack *stack) {
    if (!stack) {
        printf("ERROR: Stack doesn't exist");
        return;
    }
    if (stack->elements)
        free(stack->elements);
    stack->busy = -1;
    stack->elements = 0;
}

void deleteStack(Stack *stack) {
    if (!stack) {
        printf("ERROR: Stack doesn't exist");
        return;
    }
    clearStack(stack);
    free(stack);
}

void pushStack(Stack *stack, int element) {
    if (!stack) {
        printf("ERROR: Stack doesn't exist");
        return;
    }

    /* Description:
     *  If array hasn't been inited yet, then alloc memory for INITIAL_STACK_SIZE amount of int, update busy and size fields
     *  If all allocated memory is busy, then realloc memory (in SIZE_MULTIPLIER times more) and update size field
     *  Push element and update busy field (if it hasn't been updated yet) */
    if (!stack->size) {
        stack->size = INITIAL_STACK_SIZE;
        stack->elements = (int *) calloc(stack->size, sizeof(int));
        if (!stack->elements) {
            printf("ERROR: Cannot allocate memory for stack elements");
        }
        stack->busy = 0;
    } else {
        if (stack->size <= stack->busy + 1) {
            stack->size *= SIZE_MULTIPLIER;
            stack->elements = (int *) realloc(stack->elements, sizeof(int) * stack->size);
            if (!stack->elements) {
                printf("ERROR: Cannot allocate memory for stack elements");
            }
        }
        stack->busy++;
    }
    stack->elements[stack->busy] = element;
}

int popStack(Stack *stack) {
    if (!stack) {
        printf("ERROR: Stack doesn't exist");
        exit(1); // TODO invent error number
    }

    if (stack->busy < 0) {
        printf("ERROR: Trying tot pop from empty stack");
        exit(1); // TODO invent error number
    }

    int value = stack->elements[stack->busy];
    stack->busy--;

    return value;
}