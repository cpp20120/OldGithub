#include <iostream>
#include <vector>

template <typename T>
int binarySearch(const std::vector<T> &arr, const T &target) {
  int left = 0;
  int right = arr.size() - 1;

  while (left <= right) {
    int mid = left + (right - left) / 2;

    if (arr[mid] == target) {
      return mid; // Target found
    } else if (arr[mid] < target) {
      left = mid + 1; // Discard left half
    } else {
      right = mid - 1; // Discard right half
    }
  }

  return -1; // Target not found
}

int main() {
  std::vector<int> sortedArray = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int target = 7;

  int result = binarySearch(sortedArray, target);

  if (result != -1) {
    std::cout << "Element found at index " << result << std::endl;
  } else {
    std::cout << "Element not found" << std::endl;
  }

  return 0;
}
