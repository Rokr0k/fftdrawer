#include "dft.h"
#define __USE_MATH_DEFINES
#include <math.h>

void dft(const double complex *const x, double complex *const X, const size_t N)
{
    for (size_t k = 0; k < N; k++)
    {
        X[k] = 0;
        for (size_t n = 0; n < N; n++)
        {
            X[k] += x[n] * cexp(-2 * M_PI * I / N * k * n);
        }
        X[k] /= N;
    }
}