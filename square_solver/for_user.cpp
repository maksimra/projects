#include "for_user.h"


static void skip_line()
{
    int ch = 0;
    while((ch = getchar()) != '\n' && ch != EOF)
        continue;
}

int get_coeff (double* a, double* b, double* c)
{
    printf ("Введите коэффициенты квадратного уравнения:\n");
    int k = 0;
    while ((k = scanf ("%lf %lf %lf", a, b, c)) != 3 && k != EOF)
    {
        printf ("Некорректные значения:(\nВведите снова:\n");
        skip_line();
    }
    return (k == EOF) ? EOF : 0;
}

void print_root (double x1, double x2, int nRoots)
{
    switch (nRoots)
    {
        case ZERO_ROOTS:
            printf ("Уравнение не имеет корней.\n");
            break;
        case ONE_ROOT:
            printf ("Корень уравнения равен %.2lf\n", x1);
            break;
        case TWO_ROOTS:
            printf ("Корни уравнения %g и %g.\n", x1, x2);
            break;
        case INF_ROOTS:
            printf ("Решением является любое действительное число.\n");
            break;
        default:
            printf ("Что-то сломалось:(\n");
    }
}

int ask_if_continue (int *repeating_coeffs)
{
    printf ("Введите 1 для продолжения\n"
            "или 0 - для окончания.\n");
        if (scanf ("%d", repeating_coeffs) == EOF)
        {
            perror ("Ошибка ввода");
            return EOF;
        }
    skip_line();
    return 0;
}
