#include "stack.h"

#include "node.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Stack {
    uint32_t top;
    uint32_t capacity;
    Node **items;
} Stack;
//function creates a stack
Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack));
    if (s) {
        s->top = 0;
        s->capacity = capacity;
        s->items = (Node **) calloc(capacity, sizeof(Node));
        if (!s->items) {
            free(s);
            s = NULL;
        }
    }
    return s;
}
//function deletes the stack
void stack_delete(Stack **s) {
    if (*s && (*s)->items) {
        free((*s)->items);
        free(*s);
        *s = NULL;
    }
    return;
}
//returns true if the stack is empty
bool stack_empty(Stack *s) {
    return s->top == 0;
}
//returns true if the stack is full
bool stack_full(Stack *s) {
    return s->top == s->capacity;
}
//returns the size of the stack
uint32_t stack_size(Stack *s) {
    return s->top;
}
//pushes a node onto the stack
bool stack_push(Stack *s, Node *n) {
    if (stack_full(s)) {
        return false;
    }
    s->items[s->top] = n;
    s->top += 1;
    return true;
}
//pops a node off the stack
bool stack_pop(Stack *s, Node **n) {
    if (stack_empty(s)) {
        return false;
    }
    s->top -= 1;
    *n = s->items[s->top];
    return true;
}
//prints the stack
void stack_print(Stack *s) {
    printf("-----------------\n");
    printf("Stack: [");
    for (uint32_t i = 0; i < s->top; i++) {
        printf("(%d, %lu)", s->items[i]->symbol, s->items[i]->frequency);
        if (i != s->top - 1) {
            printf(", ");
        }
    }
    printf("]\n");
    printf("Size: %d\n", s->top);
}
