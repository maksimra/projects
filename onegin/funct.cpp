#include "onegin.h"
#include "colors.h"

/*long int memory_counter (FILE *fp)
{
    if (fp == NULL)
    {
        Error = ERROR_FOPEN;
        perror ("Ошибка открытия файла");
    }
    long current = -1;
    if ((current = ftell (fp)) == -1)
    {
        Error = ERROR_FTELL;
        perror ("Ошибка чтения исходной позиции");
    }
    if (fseek (fp, 0, SEEK_END) != 0)
    {
        Error = ERROR_FSEEK;
        perror ("Ошибка установки позиции");
    }
    long int size = 0;
    if ((size = ftell (fp)) == -1)
    {
        Error = ERROR_FTELL;
        perror ("Ошибка чтения размера файла");
    }
    if (fseek (fp, current, SEEK_SET) != 0)
    {
        Error = ERROR_FSEEK;
        perror ("Ошибка установки позиции в исходную");
    }
    return size;
}*/

void f_read (size_t size, FILE *fp, char** buffer_ptr, enum error* Error)
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
        *Error = ERROR_FSEEK;
        perror ("Ошибка установки позиции в начальную");
    }
    for (long i = 0; i < size && (buffer[i] = fgetc (fp)) != EOF; i++)
        continue;

    if (fseek (fp, position, SEEK_SET) != 0)
    {
        *Error = ERROR_FSEEK;
        perror ("Ошибка установки позиции в исходную");
    }
}
// NEEDS FREE() AFTER USE!!!
FILE* open_file_and_fill_stat (const char *NAME, struct stat *statbuf, enum error* Error)
{
    FILE *fp = fopen (NAME, "rb");
    if (fp == NULL)
        printf ("Файл не открылся :(\n");
    if (stat (NAME, statbuf) == -1)
    {
        *Error = ERROR_STAT;
        perror ("Ошибка функции stat");
    }
    return fp;
}
void error_output (enum error Error)
{
    switch (Error)
    {
        case ERROR_FOPEN:
            printf ("Ошибка открытия файла :(\n");
            break;
        case ERROR_FSEEK:
            printf ("Ошибка установки позиции в файле :(\n");
            break;
        case ERROR_FTELL:
            printf ("Ошибка чтения позиции в файле :(\n");
            break;
        case ERROR_STAT:
            printf ("Ошибка использования функции stat :(\n");
            break;
        default:
            printf ("Чтение размера файла прошло успешно!\n");
    }
}
void bubble_sort (Lines* onegin, size_t line_counter)
{
    for (int pass = 0; pass < line_counter - 1; pass++)
    {
        int nswap = 0;
        for (int i = 0; i < line_counter - pass - 1; i++)
        {
            if (my_strcmp (onegin[i].ptr, onegin[i + 1].ptr) > 0)
            {
                swap (onegin, i);
                nswap += 1;
            }
        }
        if (nswap == 0)
            break;
    }
}
//void end_bubble_sort (struct Lines* onegin, size_t line_counter) // спросить более опытных собратьев

/*int comp(const void* s1, const void* s2)
{
    return my_strcmp((const char*) s1, (const char*) s2);
}*/

int my_strcmp (char *s1, char *s2)
{
    int pos = 0;
    // *(s1 + pos) <=> s1[pos]
    for ( ; *(s1 + pos) != 0 && *(s2 + pos) != 0; pos++)
    {
        if (*(s1 + pos) != *(s2 + pos))
            break;
    }
    int pos1, pos2;
    pos1 = pos2 = pos;
    while (*(s1 + pos1) != 0 && *(s2 + pos2) != 0)
    {
        if (isalpha(*(s1 + pos1)) && isalpha (*(s2 + pos2)))
        {
            if (*(s1 + pos1) > *(s2 + pos2))
                return 1;
            else if (*(s1 + pos1) < *(s2 + pos2))
                return -1;
        }
        while (!isalpha(*(s1 + pos1)))// while, что на буквах
            pos1++;
        while (!isalpha(*(s2 + pos2))) //в цикле сидеть пока буквы или пробел
            pos2++;
    }
    return 0;
}

void swap (struct Lines* onegin, int i)
{
    char* temp = NULL;
    temp = onegin[i].ptr;
    onegin[i].ptr = onegin[i + 1].ptr;
    onegin[i + 1].ptr = temp;
    int temp_lenght = 0;
    temp_lenght = onegin[i].lenght;
    onegin[i].lenght = onegin[i + 1].lenght;
    onegin[i + 1].lenght = temp_lenght;
}

void print_size_and_numlines (size_t size, size_t num_lines)
{
    printf (PAINT_TEXT(YELLOW, "SIZE (from statbuf) = %zu\n NUMLINES = %zu\n"), size, num_lines);
}

size_t line_processing (size_t size, char* buffer_stdfread)
{
    size_t line_counter = 0;
    for (size_t k = 0 ; k < size; k++)
    {
        if (buffer_stdfread[k] == '\r')
        {
            line_counter++;
            buffer_stdfread[k] = '\0';
            // k++;
            continue;
        }
        if (buffer_stdfread[k] == '\n')
        {
            // line_counter++;
            buffer_stdfread[k] = '\0';
            continue;
        }
    }
    if (buffer_stdfread[size - 1] != '\n' && buffer_stdfread[size - 1] != '\r')
        line_counter++;

    return line_counter;
}

char** ptr_to_lines (size_t size, size_t line_counter, char* buffer_stdfread, enum error* Error)
{
    char** lines = (char**) calloc (line_counter + 1, sizeof (char*));
    if (lines == NULL)
    {
        *Error = ERROR_CALLOC;
        printf ("Ошибка выделения памяти под массив указателей!\n");
    }
    size_t a = 0;
    lines[a++] = buffer_stdfread;
    for (size_t k = 0; k < size + 1; k++)
    {
        if (buffer_stdfread[k] == '\0')
        {
            k += 2;
            lines[a] = buffer_stdfread + k;
            a++;
        }
    }
    return lines;
}

void lines_to_struct (struct Lines* onegin, size_t line_counter, char** lines)
{
    for (size_t i = 0; i < line_counter; i++)
    {
        onegin[i].lenght = lines[i + 1] - lines[i] - 2;
        onegin[i].ptr = lines[i];
    }
}

void printf_text (size_t line_counter, struct Lines* onegin)
{
    printf (PAINT_TEXT(YELLOW, "Сейчас будет распечатка текста!\n"));
    for (int i = 0; i < line_counter; i++)
        printf ("%s\n", onegin[i].ptr);
}
