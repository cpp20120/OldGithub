#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <vector>
template <typename RandomIt> void InsertionSort(RandomIt first, RandomIt last) {
  for (auto it = first + 1; it != last; ++it) {
    auto key = *it;
    auto j = it - 1;

    while (j >= first && *j > key) {
      *(j + 1) = *j;
      --j;
    }

    *(j + 1) = key;
  }
}

template <typename RandomIt> RandomIt Partition(RandomIt first, RandomIt last) {
  auto pivot = *(last - 1);
  auto i = first - 1;

  for (auto j = first; j < last - 1; ++j) {
    if (*j <= pivot) {
      ++i;
      std::swap(*i, *j);
    }
  }

  std::swap(*(i + 1), *(last - 1));
  return i + 1;
}

template <typename RandomIt>
void Quicksort(RandomIt first, RandomIt last, int depth_limit) {
  while (last - first > 16) {
    if (depth_limit == 0) {
      // Switch to heapsort if recursion depth limit is reached
      std::make_heap(first, last);
      std::sort_heap(first, last);
      return;
    }

    auto pivot = Partition(first, last);
    Quicksort(first, pivot, depth_limit - 1);
    first = pivot + 1;
  }

  InsertionSort(first, last);
}

template <typename RandomIt> void Introsort(RandomIt first, RandomIt last) {
  const int depth_limit = 2 * static_cast<int>(std::log2(last - first));

  Quicksort(first, last, depth_limit);
}

int main() {
  std::vector<int> numbers = {12, 4,  5, 6,  7, 3,  1, 15,
                              8,  10, 9, 11, 2, 14, 13};

  std::cout << "Original array: ";
  for (const auto &num : numbers) {
    std::cout << num << " ";
  }
  std::cout << "\n";

  Introsort(numbers.begin(), numbers.end());

  std::cout << "Sorted array: ";
  for (const auto &num : numbers) {
    std::cout << num << " ";
  }
  std::cout << "\n";
  std::array<double, 16> Dnumbers = {12.3, 4.2, 5.5, 5.3, 6,  7, 3,  1,
                                     15,   8,   10,  9,   11, 2, 14, 13};

  std::cout << "Original array: ";
  for (const auto &Dnum : Dnumbers) {
    std::cout << Dnum << " ";
  }
  std::cout << "\n";

  Introsort(Dnumbers.begin(), Dnumbers.end());

  std::cout << "Sorted array: ";
  for (const auto &Dnum : Dnumbers) {
    std::cout << Dnum << " ";
  }
  std::cout << "\n";
  return 0;
}
