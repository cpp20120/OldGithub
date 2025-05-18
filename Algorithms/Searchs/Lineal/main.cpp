#include <iostream>
#include <vector>

template <typename T>
int linearSearch(const std::vector<T> &arr, const T &target) {
  for (int i = 0; i < arr.size(); ++i) {
    if (arr[i] == target) {
      return i; // Target found at index i
    }
  }

  return -1; // Target not found
}

int main() {
  std::vector<int> array = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int target = 7;

  int result = linearSearch(array, target);

  if (result != -1) {
    std::cout << "Element found at index " << result << std::endl;
  } else {
    std::cout << "Element not found" << std::endl;
  }

  return 0;
}
