#include <iostream>

template <typename T, size_t N>
int ternarySearch(const T (&arr)[N], int left, int right, const T &target) {
  while (left <= right) {
    int mid1 = left + (right - left) / 3;
    int mid2 = right - (right - left) / 3;

    if (arr[mid1] == target) {
      return mid1;
    } else if (arr[mid2] == target) {
      return mid2;
    }

    if (target < arr[mid1]) {
      right = mid1 - 1;
    } else if (target > arr[mid2]) {
      left = mid2 + 1;
    } else {
      left = mid1 + 1;
      right = mid2 - 1;
    }
  }

  return -1;
}

int main() {
  int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int n = sizeof(arr) / sizeof(arr[0]);
  int target = 7;

  int result = ternarySearch(arr, 0, n - 1, target);

  if (result != -1) {
    std::cout << "Element found at index " << result << std::endl;
  } else {
    std::cout << "Element not found" << std::endl;
  }

  return 0;
}
