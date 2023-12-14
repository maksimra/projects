//#ifndef PROCESSOR_H
//#define PROCESSOR_H

#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <sys\stat.h>
#include <assert.h>
#include <stdlib.h>

enum Proc_error
{
    PROC_NO_ERROR,
    PROC_ERROR_FOPEN,
    PROC_ERROR_CMDS,
    PROC_ERROR_STAT,
    PROC_ERROR_FSEEK

};

// struct Processor
// {
//     enum proc_error error = PROC_NO_ERROR; //ещё имя файла туда положить


FILE* open_file_and_fill_stat (const char *NAME, struct stat *statbuf, enum Proc_error* Error);
void  f_read                  (size_t size, FILE *fp, char** buffer_ptr, enum Proc_error* Error);
void  check_argc              (int argc);
//#endif
