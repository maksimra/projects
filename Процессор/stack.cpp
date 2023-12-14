#include "Stack.h"

void StackCtor (struct Stack *stk, size_t capacity, enum Stk_error* Error)
{
    *Error = STK_NO_ERROR; // поменять
    if (stk->data != NULL)
        printf ("Stack уже был создан!!!\n");
    if (capacity <= 0)
    {
        *Error = STK_NEGATIVE_CAPACITY;
        return;
    }
    if ((stk->data = (STK_ELEMENT*) calloc (capacity, sizeof (STK_ELEMENT))) == NULL)
    {
        *Error = STK_CALLOC_FAIL;
        return;
    }
    stk->size = 0;
    stk->capacity = capacity;
}

void StackDtor (struct Stack *stk)
{
    free (stk->data);
    stk->data = NULL;
    stk->capacity = 0;
    stk->size = 0;
}

void StackPush (struct Stack *stk, int elem, enum Stk_error* Error) // переменная с маленькой буквы
{
    if (stk->size >= stk->capacity)
    {
        STK_ELEMENT *temp = (STK_ELEMENT*) realloc (stk->data, stk->capacity * 2); //realloc в отд функцию
        if (temp == NULL)
        {
            *Error = STK_REALLOC_FAIL;
            printf ("Ошибка выделения дополнительной памяти\n"); //лучше не писать printf (ошибка в дампе) дамп печатает в файл с логами
            return; // в ctor предоставить выбор, куда выводить ошибки (открывать файл для записи и передавать в стэк
        } //cppreference __LINE__ __func__ __PRETTY_FUNCTION__ __FILE__
        stk->data = temp;
    }
    *(stk->data + stk->size) = elem;
    ++(stk->size);
}

void StackClear (struct Stack *stk)
{
    while (stk->size > 0)
    {
        (stk->size)--;
        *(stk->data + stk->size) = 0; //функция заполняет кусок памяти определенным значением func(указатель на начало, кол-во эл-ов, указатель на элемент (которым заполняю) и его размер
        // и через мемкопи
    }
}

void FillStack  (struct Stack *stk, size_t capacity, STK_ELEMENT filler)
{
    for (size_t i = 0; i < capacity; i++)
    {
        stk->data[i] = filler;
    } // cppreference: memcpy() memset()  почему memcpy а не memset
}


int StackPop (struct Stack *stk, enum Stk_error* Error)
{
    if (stk->size <= 0)
    {
        *Error = STK_POP_FAIL; //разбить на функции (реалокация, ошибку возвращать, а element по указателю возвращать)
        //если NULL, что элемент убираю, но не возвращаю
        return POISON;
    }
    *(stk->data + stk->size - 1) = 0;
    --(stk->size);
    STK_ELEMENT elem = *(stk->data + stk->size - 1);
    if (stk->size * 2 < stk->capacity / SAMPLE) // большими буквами констнту
    {
        STK_ELEMENT *temp = (int*) realloc (stk->data, stk->capacity / 2);
        if (temp == NULL)
        {
            *Error = STK_REALLOC_FAIL;
            return POISON;
        }
        else
            stk->data = temp;
    }
    return elem;
}

// char* err = PrintError(stkErr);
// err[3] = 'h';
// err[4] = 'u';
// ...

void PrintError (enum Stk_error Error)
{ //возврщает char*
    switch (Error) //функция должна возвращать строку
    {
        case STK_NO_ERROR:
            printf ("STACK: Ошибок в работе функций не выявлено.\n");
            break;
        case STK_REALLOC_FAIL:
            printf ("STACK: Ошибка в работе функции realloc.\n");
            break;
        case STK_POP_FAIL:
            printf ("STACK: Ошибка в работе функции pop.\n");
            break;
        case STK_CALLOC_FAIL:
            printf ("STACK: Ошибка в выделении памяти (calloc).\n");
            break;
        case STK_NEGATIVE_CAPACITY:
            printf ("STACK: Отрицательное значение capacity.\n");
            break;
        default:
            printf ("STACK: Куда делся мой enum ошибок?\n");
    }
}
