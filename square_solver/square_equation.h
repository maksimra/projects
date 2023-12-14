#ifndef SQUARE_EQUATION_H
#define SQUARE_EQUATION_H

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

int     compare_doubles          (double x, double y);

void    solve_quadratic_equation (const double a, const double b, const double c, double* x1, double* x2, int* nRoots);

void    solve_linear_equation    (const double b, const double c, int* nRoots, double* x1);

#endif //SQUARE_EQUATION_H
