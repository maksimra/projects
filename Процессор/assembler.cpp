#include "assembler.h"

int main (int argc, char* argv[])
{
    enum error Error = NO_ERROR;
    const char *NAME = argv[1]; // parseArgs


    struct stat statbuf = {};
    FILE *source_code_file = open_file_and_fill_stat (NAME, &statbuf, &Error);
    char *buffer_stdfread = NULL;
    f_read (statbuf.st_size, source_code_file, &buffer_stdfread, &Error);

    size_t line_counter = line_processing (statbuf.st_size, buffer_stdfread);
    char** lines = ptr_to_lines (statbuf.st_size, line_counter, buffer_stdfread, &Error);

    FILE *assemble = fopen ("assembler.txt", "w");
    char cmd[MAX_SYMB] = {0};
    double digit = NAN;
    printf ("nlines = %d\n", line_counter);

    for (size_t i = 0; i < line_counter - 1; i++)
    {
        sscanf (lines[i], "%s", cmd);
        for (size_t j = 0; j < N_CMDS; j++)
        {
            if (strncmp (cmd, CMD[j].name_cmd, MAX_SYMB) != 0)
            {
                continue;
            }
            fprintf (assemble, "%d", CMD[j].number_of_cmd);
            if (CMD[j].name_cmd == "PUSH")
            {
                sscanf (lines[i] + strlen ("PUSH"), "%lf", &digit);
                fprintf (assemble, " %g", digit);
            }
            fprintf (assemble, "\n");
        }
    }
    fprintf (assemble, "\0");
    fclose (assemble);
    return 0;
}
