#include "stack.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct Stack {
    uint32_t top;
    uint32_t capacity;
    int64_t *items;
} Stack;
//create stack
Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack));
    if (s) {
        s->top = 0;
        s->capacity = capacity;
        s->items = (int64_t *) calloc(capacity, sizeof(int64_t));
        if (!s->items) {
            free(s);
            s = NULL;
        }
    }
    return s;
}
//delete stack
void stack_delete(Stack **s) {
    if (*s && (*s)->items) {
        free((*s)->items);
        free(*s);
        *s = NULL;
    }
    return;
}
//returns the size of the stack
uint32_t stack_size(Stack *s) {
    return s->top;
}
//returns if the stack is empty
bool stack_empty(Stack *s) {
    return s->top == 0;
}
//returns if the stack is full
bool stack_full(Stack *s) {
    return s->top == s->capacity;
}
//pushes an item on to the stack
bool stack_push(Stack *s, uint32_t x) {
    if (stack_full(s)) {
        return false;
    }
    s->items[s->top] = x;
    s->top += 1;
    return true;
}
//pops an item off the stack
bool stack_pop(Stack *s, uint32_t *x) {
    if (stack_empty(s)) {
        return false;
    }
    s->top -= 1;
    *x = s->items[s->top];
    return true;
}
//provides the first item on the stack
bool stack_peek(Stack *s, uint32_t *x) {
    if (stack_empty(s)) {
        return false;
    }
    *x = s->items[s->top - 1];
    return true;
}
//copies a source stack into a destination stack
void stack_copy(Stack *dst, Stack *src) {
    uint32_t job = 0;
    uint32_t *jv;
    jv = &job;
    while (!stack_empty(dst)) {
        stack_pop(dst, jv);
    }
    if (dst->capacity == src->capacity) {
        for (uint32_t i = 0; i < stack_size(src); i++) {
            stack_push(dst, src->items[i]);
        }
        return;
    }
}
//prints the stack
void stack_print(Stack *s, FILE *outfile, char *cities[]) {
    for (uint32_t i = 0; i < s->top; i++) {
        fprintf(outfile, "%s", cities[s->items[i]]);
        if (i + 1 != s->top) {
            fprintf(outfile, " -> ");
        }
    }
    fprintf(outfile, "\n");
}
