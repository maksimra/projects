#include "Stack.h"
#include "processor.h"

int main (int argc, char* argv[])
{
    enum Proc_error proc_error = PROC_NO_ERROR; //допилить и проверять везде
    enum Stk_error stk_error = STK_NO_ERROR;
    check_argc(argc);
    const char* NAME = argv[1];

    struct stat statbuf = {};

    FILE *code_file = open_file_and_fill_stat (NAME, &statbuf, &proc_error); // потом будут функции которые возвращают ошибка самого процессора (деление на ноль, например)

    if (proc_error != PROC_NO_ERROR)
    {
        printf ("Ъуъ!");
        return proc_error; // вынести в функцию
    }

    char *buffer_stdfread = NULL;
    fread (buffer_stdfread, sizeof (double), statbuf.st_size, code_file);
    int j = 0;
    while (buffer_stdfread[j] != '\0')
    {
        printf ("%d\n", buffer_stdfread[j]);
        j++;
    }
    //f_read (statbuf.st_size, code_file, &buffer_stdfread, &proc_error);

    for (size_t i = 0; i < statbuf.st_size && buffer_stdfread[i] != -1; i++)
    {
        struct Stack proc_stk = {};
        StackCtor  (&proc_stk, BASIC_CAPACITY, &stk_error);
        double a = NAN;
        double b = NAN;
        printf ("buffer_stdfread[i] = %d\n", buffer_stdfread[i]);
        switch (buffer_stdfread[i])
        {
            case 1:
                printf ("Зашёл в case 1\n");
                i += 2;
                StackPush (&proc_stk, buffer_stdfread[i], &stk_error);
                break;
            case 2:
                printf ("Зашёл в case 2\n");
                a = StackPop (&proc_stk, &stk_error);
                b = StackPop (&proc_stk, &stk_error);
                StackPush (&proc_stk, a + b, &stk_error);
                break;
            case 3:
                printf ("Зашёл в case 3\n");
                a = StackPop (&proc_stk, &stk_error);
                b = StackPop (&proc_stk, &stk_error);
                StackPush (&proc_stk, b - a, &stk_error);
                break;
            case 4:
                printf ("Зашёл в case 4\n");
                a = StackPop (&proc_stk, &stk_error);
                b = StackPop (&proc_stk, &stk_error);
                StackPush (&proc_stk, a * b, &stk_error);
                break;
            case 5:
                printf ("Зашёл в case 5\n");
                a = StackPop (&proc_stk, &stk_error);
                b = StackPop (&proc_stk, &stk_error);
                StackPush (&proc_stk, b / a, &stk_error);
                break;
            case 6:
                printf ("Зашёл в case 6\n");
                printf ("Результат: %d\n", StackPop (&proc_stk, &stk_error));
                break;
            default:
                printf ("Зашёл в default\n");
                proc_error = PROC_ERROR_CMDS;
        }
        while (isspace (buffer_stdfread[i]))
            i++;
    }
    return 0;
}
