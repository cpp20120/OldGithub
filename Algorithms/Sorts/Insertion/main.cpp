#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

template <typename ForwardIt, typename Compare = std::less<>>
void insertionSort(ForwardIt begin, ForwardIt end, Compare comp = Compare()) {
  for (auto it = begin; it != end; ++it) {
    auto current = std::move(*it);
    auto location = std::distance(begin, it);

    auto pos = it;
    while (pos != begin && comp(current, *(pos - 1))) {
      *pos = std::move(*(pos - 1));
      --pos;
    }
    *pos = std::move(current);
  }
}

auto main() -> int {
  std::vector<int> intData = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
  insertionSort(intData.begin(), intData.end());
  for (const auto &element : intData) {
    std::cout << element << " ";
  }
  std::cout << "\n";

  std::array<int, 8> arrData = {23, 32, 31, 3, 4, 5, 56, 9};
  insertionSort(arrData.begin(), arrData.end());
  for (const auto &element : arrData) {
    std::cout << element << " ";
  }

  std::cout << "\n";

  std::vector<double> doubleData = {3.14, 1.41, 2.71, 1.61, 1.73};
  insertionSort(doubleData.begin(), doubleData.end());
  for (const auto &element : doubleData) {
    std::cout << element << " ";
  }
  std::cout << "\n";

  std::array<double, 5> doubleArrData = {3.14, 1.41, 2.71, 1.61, 1.73};
  insertionSort(doubleData.begin(), doubleData.end());
  for (const auto &element : doubleData) {
    std::cout << element << " ";
  }
  std::cout << "\n";


  return 0;
}
