#include <iostream>
#include <vector>
#include <array>

template <typename T, typename Container, typename Iterator>
void heapify(Container& arr, const int size, Iterator it) {
    auto index = std::distance(arr.begin(), it);
    auto largest = index;
    auto left = 2 * index + 1;
    auto right = 2 * index + 2;

    if (left < size && arr[left] > arr[largest]) {
        largest = left;
    }

    if (right < size && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != index) {
        std::swap(arr[index], arr[largest]);
        heapify<T>(arr, size, arr.begin() + largest);
    }
}

template <typename T, typename Container, typename Iterator>
void heapSort(Container& arr, Iterator begin, Iterator end) {
    const int size = std::distance(begin, end);

    // Build max heap
    for (int i = size / 2 - 1; i >= 0; i--) {
        heapify<T>(arr, size, begin + i);
    }

    // Heap sort
    for (int i = size - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        heapify<T>(arr, i, begin);
    }
}

int main() {
    std::vector<int> vec = {12, 11, 13, 5, 6, 7};
    std::array<double, 7> arr = {12.1, 11.5, 13.7, 5.3, 6.2, 7.9, 2.4};

    heapSort<int>(vec, vec.begin(), vec.end());
    heapSort<double>(arr, arr.begin(), arr.end());

    for (const auto& num : vec) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    for (const auto& num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
