#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>

typedef int STK_ELEMENT;

const size_t BASIC_CAPACITY = 50;

enum Stk_error
{
    STK_NO_ERROR,
    STK_REALLOC_FAIL = 1,
    STK_POP_FAIL,
    STK_CALLOC_FAIL,
    STK_NEGATIVE_CAPACITY
};

struct Stack
{
    STK_ELEMENT *data;
    size_t size;
    size_t capacity;
};

const int POISON = 666;

const int SAMPLE = 2;

void StackCtor  (struct Stack *stk, size_t capacity, enum Stk_error* Error);

void StackDtor  (struct Stack *stk);

void StackPush  (struct Stack *stk, STK_ELEMENT elem, enum Stk_error* Error);

int  StackPop   (struct Stack *stk, enum Stk_error* Error);

void StackClear (struct Stack *stk);

void PrintError (enum Stk_error Error);

void FillStack  (struct Stack *stk, size_t capacity, STK_ELEMENT filler);

#endif
