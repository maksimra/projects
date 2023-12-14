#include "compare_doubles.h"

const  double limit = 1e-6;

int compare_doubles (double x, double y)
{
    return fabs(x - y) < limit;
}
