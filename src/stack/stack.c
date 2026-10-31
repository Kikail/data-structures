//
// Created by killi on 31/10/2026.
//
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

Stack* Stack_CreateEmpty() {
    Stack* stack = (Stack*) malloc(sizeof(Stack));
    if (!stack) return NULL;
    stack->top = 0;
    stack->capacity = STACK_DEFAULT_CAPACITY;
    stack->stack = calloc(STACK_DEFAULT_CAPACITY, sizeof(void*));
    return stack;
}

Stack* Stack_CreateEmptyWithCapacity(unsigned int capacity) {
    Stack* stack = (Stack*) malloc(sizeof(Stack));
    if (!stack) return NULL;
    stack->top = 0;
    stack->capacity = capacity;
    stack->stack = calloc(capacity, sizeof(void*));
    return stack;
}

bool Stack_IsEmpty(Stack* stack) {
    if (!stack) return true;
    return stack->top == 0;
}

bool Stack_IsFull(Stack* stack) {
    if (!stack) return false;
    return stack->top == stack->capacity;
}

bool Stack_Push(Stack* stack, void* data) {
    if (!stack || !data || Stack_IsFull(stack)) return false;
    stack->stack[stack->top] = data;
    stack->top += 1;
    return true;
}

void* Stack_Pop(Stack* stack) {
    if (!stack || Stack_IsEmpty(stack)) return NULL;
    stack->top -= 1;
    void* data = stack->stack[stack->top];
    stack->stack[stack->top] = NULL;
    return data;
}

void Stack_Destroy(Stack* stack) {
    if (!stack) return;
    free(stack->stack);
    free(stack);
}

void Stack_Print(Stack* stack) {
    if (!stack) return;
    printf("Stack[\n");
    if (!Stack_IsEmpty(stack)) {
        for (unsigned int i = 0; i < stack->top; i++) {
            printf("\t[%d]: 0x%p\n", i, stack->stack[i]);
        }
    }
    printf("]\n");
}