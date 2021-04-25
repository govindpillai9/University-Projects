#include <stdbool.h>
#include <stdint.h>
#include "stack.h"

typedef struct Stack Stack {
	uint32_t top;
	uint32_t capacity;
	int64_t *items;
} Stack;

Stack *stack_create(uint32_t capacity)

void stack_delete(Stack **s);

bool stack_empty(Stack *s);

uint32_t stack_size(Stack *s);

bool stack_push(Stack *s, int64_t x);

bool stack_pop(Stack *s, int64_t *x);

void stack_print(Stack *s);

