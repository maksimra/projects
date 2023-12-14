#ifndef FOR_USER_H
#define FOR_USER_H

#include <stdio.h>

enum count_of_roots
{
    ZERO_ROOTS  = 0,
    ONE_ROOT    = 1,
    TWO_ROOTS   = 2,
    INF_ROOTS   = 3
};

static void skip_line       ();
int         get_coeff       (double* a, double* b, double* c);
void        print_root      (double x1, double x2, int nRoots);
int         ask_if_continue (int *repeating_coeffs);

#endif //FOR_USER_H
