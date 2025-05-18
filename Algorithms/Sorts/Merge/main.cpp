#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

// Merge function for merging two sorted sub-arrays
template <typename T, typename Iterator>
void merge(Iterator left, Iterator middle, Iterator right) {
    std::vector<typename T::value_type> temp(std::distance(left, right));

    auto i = left;
    auto j = middle;
    auto k = temp.begin();

    while (i < middle && j < right) {
        if (*i <= *j) {
            *k = *i;
            i++;
        } else {
            *k = *j;
            j++;
        }
        k++;
    }

    while (i < middle) {
        *k = *i;
        i++;
        k++;
    }

    while (j < right) {
        *k = *j;
        j++;
        k++;
    }

    std::copy(temp.begin(), temp.end(), left);
}

// Merge Sort function for std::vector or std::array
template <typename T, typename Iterator>
void mergeSort(Iterator left, Iterator right) {
    if (std::distance(left, right) > 1) {
        auto middle = left + std::distance(left, right) / 2;

        mergeSort<T>(left, middle);
        mergeSort<T>(middle, right);

        merge<T>(left, middle, right);
    }
}

auto main() -> int {
    std::vector<int> intData = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    mergeSort<std::vector<int>>(intData.begin(), intData.end());
    for (const auto &element : intData) {
        std::cout << element << " ";
    }
    std::cout << "\n";

    std::array<int, 8> arrData = {23, 32, 31, 3, 4, 5, 56, 9};
    mergeSort<std::array<int, 8>>(arrData.begin(), arrData.end());
    for (const auto &element : arrData) {
        std::cout << element << " ";
    }
    std::cout << "\n";

    std::vector<double> doubleData = {3.14, 1.41, 2.71, 1.61, 1.73};
    mergeSort<std::vector<double>>(doubleData.begin(), doubleData.end());
    for (const auto &element : doubleData) {
        std::cout << element << " ";
    }
    std::cout << "\n";

    std::array<double, 5> doubleArrData = {3.14, 1.41, 2.71, 1.61, 1.73};
    mergeSort<std::array<double, 5>>(doubleArrData.begin(), doubleArrData.end());
    for (const auto &element : doubleArrData) {
        std::cout << element << " ";
    }
    std::cout << "\n";

    return 0;
}
