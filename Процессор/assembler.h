#include <stdio.h>
#include <math.h>
#include <string.h>
#include <sys\stat.h>

enum error {NO_ERROR,
            ERROR_FOPEN,
            ERROR_FSEEK,
            ERROR_FTELL,
            ERROR_STAT,
            ERROR_STRCHR,
            ERROR_CALLOC};



enum CMD   {PUSH = 1,
            ADD = 2,
            SUB = 3,
            MUL = 4,
            DIV = 5,
            OUT = 6,
            HLT = -1};


const int MAX_SYMB = 20;

struct Cmds
{
    const char* name_cmd;
    enum CMD number_of_cmd;
};

const Cmds CMD[] = {
    {"PUSH", PUSH},
    {"ADD", ADD},
    {"SUB", SUB},
    {"MUL", MUL},
    {"DIV", DIV},
    {"OUT", OUT},
    {"HLT", HLT}
};

const size_t N_CMDS = sizeof (CMD) / sizeof (CMD[0]);

void   f_read                  (size_t size, FILE *fp, char** buffer, enum error* Error);
FILE*  open_file_and_fill_stat (const char *NAME, struct stat *statbuf, enum error* Error);
char** ptr_to_lines            (size_t size, size_t line_counter, char* buffer_stdfread, enum error* Error);
size_t line_processing         (size_t size, char* buffer_stdfread);
