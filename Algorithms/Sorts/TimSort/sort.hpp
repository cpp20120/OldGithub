#ifndef SORT_HPP
#define SORT_HPP

#include <algorithm>
#include <concepts>
#include <iterator>
#include <vector>

template <typename T>
concept Sortable = requires(T a, T b) {
  { a < b } -> std::convertible_to<bool>;
};

template <typename T>
  requires std::is_integral_v<T>
constexpr auto minrun(T n) {
  int r = 0;
  while (n >= 64) {
    r |= n & 1;
    n >>= 1;
  }
  return n + r;
}

template <typename RandomIt>
  requires std::random_access_iterator<RandomIt> &&
           Sortable<typename std::iterator_traits<RandomIt>::value_type>
constexpr void insertion_sort(RandomIt first, RandomIt last) {
  for (auto it = first + 1; it < last; ++it) {
    auto val = std::move(*it);
    auto pos = std::upper_bound(first, it, val);
    std::move_backward(pos, it, it + 1);
    *pos = std::move(val);
  }
}

template <typename RandomIt>
  requires std::random_access_iterator<RandomIt> &&
           Sortable<typename std::iterator_traits<RandomIt>::value_type>
constexpr void merge_runs(RandomIt first, RandomIt middle, RandomIt last) {
  std::vector<typename std::iterator_traits<RandomIt>::value_type> left(first,
                                                                        middle);
  std::vector<typename std::iterator_traits<RandomIt>::value_type> right(middle,
                                                                         last);

  auto it_left = left.begin();
  auto it_right = right.begin();
  RandomIt it = first;

  while (it_left != left.end() && it_right != right.end()) {
    if (*it_left < *it_right) {
      *it++ = std::move(*it_left++);
    } else {
      *it++ = std::move(*it_right++);
    }
  }

  std::move(it_left, left.end(), it);
  std::move(it_right, right.end(), it);
}

template <typename RandomIt>
  requires std::random_access_iterator<RandomIt> &&
           Sortable<typename std::iterator_traits<RandomIt>::value_type>
constexpr void tim_sort(RandomIt first, RandomIt last) {
  int n = last - first;
  int min_run = minrun(n);

  for (int i = 0; i < n; i += min_run) {
    insertion_sort(first + i, std::min(first + i + min_run, last));
  }

  for (int size = min_run; size < n; size *= 2) {
    for (int left = 0; left < n; left += 2 * size) {
      int mid = left + size;
      int right = std::min(left + 2 * size, n);
      merge_runs(first + left, first + mid, first + right);
    }
  }
}

#endif