#include "square_equation.h"
#include "for_user.h"

void solve_quadratic_equation (const double a, const double b, const double c, double *x1, double *x2, int *nRoots)
{
    if (compare_doubles(0, a))
    {
        solve_linear_equation (b, c, nRoots, x1);
        return;
    }

    const double D = b * b - 4 * a * c;

    if (D < 0)
    {
        *nRoots = ZERO_ROOTS;
    }
    else if (compare_doubles(0, D))
    {
        *x1 = -b / 2 * a;
        *nRoots = ONE_ROOT;
    }
    else
    {
        double sqrtD = sqrt(D);
        *x1 = (-b - sqrtD) / (2 * a);
        *x2 = (-b + sqrtD) / (2 * a);
        *nRoots = TWO_ROOTS;
    }
}

void solve_linear_equation (const double b, const double c, int *nRoots, double *x1)
{
    if (compare_doubles(0, b))
    {
        *nRoots = (compare_doubles(0, c)) ? INF_ROOTS : ZERO_ROOTS;
    }
    else
    {
        *x1 = compare_doubles(0, - c / b) ? 0 : (-c / b);
        *nRoots = ONE_ROOT;
    }
}
