#include "square_equation.h"
#include "for_user.h"
#include "tests.h"

int main()
{
    double a = NAN, b = NAN, c = NAN, x1 = NAN, x2 = NAN;
    int nRoots = -1;
    int repeating_coeffs = 1;
    printf ("Поможем с решением квадратного уравнения :)\n");
    while (repeating_coeffs == 1)
    {
        if (get_coeff (&a, &b, &c) == EOF)
        {
            printf ("Некорректные коэффициенты!!!\n");
            return -1;
        }

        solve_quadratic_equation (a, b, c, &x1, &x2, &nRoots);

        print_root (x1, x2, nRoots);

        if (ask_if_continue (&repeating_coeffs) == EOF)
        {
            printf ("Некорректные данные!!!\n");
            return -1;
        } //если EOF вернуть ошибку
    }
    printf ("Тогда переходим к тестам.\n");

    tests ();

    return 0;
}

