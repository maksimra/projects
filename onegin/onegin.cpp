#include "onegin.h"
#include "colors.h"

int main (const int argc, const char** argv)
{
    enum error Error = NO_ERROR;
    const char *NAME = argv[1];
    struct stat statbuf = {}; // га первую указатель не ставится


    FILE *fp = open_file_and_fill_stat (NAME, &statbuf, &Error);
    char *buffer_stdfread = NULL;
    f_read (statbuf.st_size, fp, &buffer_stdfread, &Error);

    size_t line_counter = line_processing (statbuf.st_size, buffer_stdfread);
    print_size_and_numlines (statbuf.st_size, line_counter);
    char** lines = ptr_to_lines (statbuf.st_size, line_counter, buffer_stdfread, &Error);
    // struct Lines onegin[line_counter] = {};
    Lines* onegin = (Lines*) calloc(line_counter, sizeof(onegin[0]));

    lines_to_struct (onegin, line_counter, lines);
    error_output (Error);
    // printf("<%s>\n", onegin[0].ptr);
    printf_text (line_counter, onegin);
    bubble_sort (onegin, line_counter);
    printf_text (line_counter, onegin);
    /*printf ("Вывод структуры строк:\n");
    for (size_t i = 0; i < line_counter; i++)
    {
        printf ("onegin[%d].lenght = %d\n", i, onegin[i].lenght);
    }*/
    // printf ("\n\n>>>>>Сейчас будет печать по указателям\n\n");
    // for (size_t k = 0; k < line_counter - 1; k++)
    //     printf ("%s\n", lines[k]);
    /*printf ("\n\n>>>>>Сейчас будет отсортированная печать\n\n");
    for (size_t k = 0; k < line_counter - 1; k++)
    printf ("%s\n", lines[k]);*/
    return 0;
}
