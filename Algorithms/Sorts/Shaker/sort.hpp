#ifndef SORT_HPP
#define SORT_HPP

#include <array>
#include <concepts>

template <typename T>
concept Comparable = requires(T a, T b) {
  { a < b } -> std::convertible_to<bool>;
  { a > b } -> std::convertible_to<bool>;
};

template <Comparable T, std::size_t N>
constexpr std::array<T, N> shaker_sort(std::array<T, N> arr) {
  bool swapped = true;
  std::size_t start = 0;
  std::size_t end = N - 1;

  while (swapped) {
    swapped = false;
    for (std::size_t i = start; i < end; ++i) {
      if (arr[i] > arr[i + 1]) {
        std::swap(arr[i], arr[i + 1]);
        swapped = true;
      }
    }

    if (!swapped) {
      break;
    }

    swapped = false;
    --end;

    for (std::size_t i = end; i > start; --i) {
      if (arr[i - 1] > arr[i]) {
        std::swap(arr[i - 1], arr[i]);
        swapped = true;
      }
    }
    ++start;
  }

  return arr;
}

#endif
