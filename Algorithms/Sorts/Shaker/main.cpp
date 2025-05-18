#include <print>

#include "sort.hpp"

constexpr std::array<int, 6> arr = {5, 2, 9, 1, 5, 6};
constexpr auto sortedArr = shaker_sort(arr);

int main() {
  for (const auto& elem : sortedArr) std::println("{}", elem, '\n');

  return 0;
}