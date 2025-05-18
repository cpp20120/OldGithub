#include <array>

#include <fmt/ranges.h>
#include "sort.hpp"

auto main() -> int {
  std::vector<int> vec = {5, 2, 9, 1, 5, 6, 3, 8};
  std::array<int, 8> arr = {5, 2, 9, 1, 5, 6, 3, 8};

  fmt::print("Original vector: ");
  fmt::print("{}\n", vec);

  tim_sort(vec.begin(), vec.end());

  fmt::print("Sorted vector: ");
  fmt::print("{}\n", vec);

  fmt::print("Original array: ");
  fmt::print("{}\n", arr);

  tim_sort(arr.begin(), arr.end());

  fmt::print("Sorted array: ");
  fmt::print("{}\n", arr);

  return 0;
}