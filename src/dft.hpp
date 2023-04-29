#pragma once

#include <complex>
#include <vector>

using namespace std::complex_literals;

namespace fft
{
    /// @brief Perform Discrete Fourier Transform with complex numbers
    /// @param x Input array
    /// @returns Output array
    template <typename T>
    std::vector<std::complex<T>> dft(const std::vector<std::complex<T>> &x)
    {
        const T PI = std::acos(-1);
        const size_t N = x.size();

        std::vector<std::complex<T>> X;
        X.resize(N, {});

        for (size_t k = 0; k < N; k++)
        {
            X[k] = 0;
            for (size_t n = 0; n < N; n++)
            {
                X[k] += x[n] * std::exp(-2 * PI * std::complex<T>{0, 1} / static_cast<T>(N) * static_cast<T>(k) * static_cast<T>(n));
            }
            X[k] /= N;
        }

        return X;
    }
}