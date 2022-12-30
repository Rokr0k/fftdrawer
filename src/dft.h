#ifndef __FFT_H__
#define __FFT_H__

#include <stddef.h>
#include <complex.h>

/// @brief Perform Discrete Fourier Transform with complex numbers
/// @param x Input array
/// @param X Output array
/// @param N Length of the array
void dft(const double complex *const x, double complex *const X, const size_t N);

#endif