#include "tests.h"
#include "square_equation.h"

void tests (void)
{
    FILE *fp = fopen ("Info for tests.txt", "r");
    if (fp == NULL)
    {
        printf ("Ошибка открытия файла\n");
        return;
    }
    int Ntests = 0;
    fscanf (fp, "%d", &Ntests);
    double a = NAN, b = NAN, c = NAN;
    double x1 = NAN, x2 = NAN;
    double x1ref = NAN, x2ref = NAN;
    int nRoots = -1, nRootsref = -1;

    for (int i = 0; i < Ntests; i++)
    {
        printf (PAINT_TEXT(WHITE, "Тест номер %d:\n"), i + 1);
        fscanf (fp, " %lf%lf%lf", &a, &b, &c);
        printf ("a = %.2lf, b = %.2lf, c = %.2lf\n", a, b, c);
        solve_quadratic_equation (a, b, c, &x1, &x2, &nRoots);
        fscanf (fp, "%lf%lf%d", &x1ref, &x2ref, &nRootsref);
        printf (PAINT_TEXT(YELLOW, "Решение в системе:\n"));
        print_root (x1, x2, nRoots);
        printf (PAINT_TEXT(RED, "Эталонное решение:\n"));
        print_root (x1ref, x2ref, nRootsref);
    }
    fclose (fp);
}
