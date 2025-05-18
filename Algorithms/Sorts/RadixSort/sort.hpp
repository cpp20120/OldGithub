#ifndef SORT_HPP
#define SORT_HPP

#include <array>
#include <concepts>
#include <utility>


// Concept to constrain types to integral types
template<typename T>
concept Integral = std::is_integral_v<T>;

// Function to get the maximum element in the array
template<Integral T, std::size_t N>
consteval T getMax(const std::array<T, N>& arr) {
    T max = arr[0];
    for (std::size_t i = 1; i < N; ++i) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

// Function to count sort the array based on the given digit place
template<Integral T, std::size_t N>
constexpr void countSort(std::array<T, N>& arr, T exp) {
    std::array<T, N> output{};
    std::array<int, 10> count{};

    // Store count of occurrences in count[]
    for (std::size_t i = 0; i < N; ++i) {
        ++count[(arr[i] / exp) % 10];
    }

    // Change count[i] so that it contains the actual position of this digit in output[]
    for (std::size_t i = 1; i < 10; ++i) {
        count[i] += count[i - 1];
    }

    // Build the output array
    for (std::size_t i = N; i > 0; --i) {
        output[count[(arr[i - 1] / exp) % 10] - 1] = arr[i - 1];
        --count[(arr[i - 1] / exp) % 10];
    }

    // Copy the output array to arr[], so that arr now contains sorted numbers
    for (std::size_t i = 0; i < N; ++i) {
        arr[i] = output[i];
    }
}

// Radix Sort implementation
template<Integral T, std::size_t N>
consteval void radixSort(std::array<T, N>& arr) {
    T max = getMax(arr);

    for (T exp = 1; max / exp > 0; exp *= 10) {
        countSort(arr, exp);
    }
}
#endif