#include "processor.h"

void check_argc (int argc)
{
    if (argc > 2)
        printf ("warning: введено больше двух аргументов командной строки!");
}

FILE* open_file_and_fill_stat (const char *NAME, struct stat *statbuf, enum Proc_error* Error)
{
    FILE *fp = fopen (NAME, "rb");
    if (fp == NULL)
        printf ("Файл не открылся :(\n");
    if (stat (NAME, statbuf) == -1)
    {
        *Error = PROC_ERROR_STAT;
        perror ("Ошибка функции stat");
    }
    return fp;
}

void f_read (size_t size, FILE *fp, char** buffer_ptr, enum Proc_error* Error)
{
    assert (fp != 0);

    char* buffer = (char*) calloc (size + 1, sizeof (char));
    *buffer_ptr = buffer;
    if (buffer == NULL)
    {
        perror ("Ошибка в выделении динамической памяти");
    }
    int position = ftell (fp);
    if (fseek (fp, 0, SEEK_SET) != 0)
    {
        *Error = PROC_ERROR_FSEEK;
        perror ("Ошибка установки позиции в начальную");
    }
    for (long i = 0; i < size && (buffer[i] = fgetc (fp)) != EOF; i++)
        continue;

    if (fseek (fp, position, SEEK_SET) != 0)
    {
        *Error = PROC_ERROR_FSEEK;
        perror ("Ошибка установки позиции в исходную");
    }
}
