#include <algorithm>
#include <iostream>
#include <vector>
#include <array>

template<typename RandomIt, typename Compare = std::less<>>
void quickSort(RandomIt begin, RandomIt end, Compare comp = Compare{}) {
    if (std::distance(begin, end) <= 1) {
        return;
    }
    auto pivot = *std::next(begin, std::distance(begin, end) / 2);

    auto left = std::partition(begin, end, [&](const auto& elem){ return comp(elem, pivot); });
    auto right = std::partition(left, end, [&](const auto& elem){ return !comp(pivot, elem); });

    quickSort(begin, left, comp);
    quickSort(right, end, comp);
}


auto main() -> int {
    std::vector<int> intVecData = {3, 34, 34, 1, 5, 7, 8, 2, 56, 4, 9};
    quickSort(intVecData.begin(), intVecData.end());
    std::cout<< "Double vector sorted: ";
    for (const auto& element : intVecData) {
        std::cout << element << " ";
    }
    std::cout << "\n";

    std::vector<double> doubleVecData = {3.14, 1.41, 2.71,  1.61, 1.73};
    quickSort(doubleVecData.begin(), doubleVecData.end());
    std::cout<< "Double vector sorted: ";
    for (const auto& element : doubleVecData) {
        std::cout << element << " ";
    }
    std::cout << "\n";

    std::array<int, 5> intData = {3, 34, 34, 1, 5};
    quickSort(intData.begin(), intData.end());
    std::cout<< "Integer array sorted: ";
    for (const auto& element: intData) {
        std::cout<< element << " ";
    }
    std::cout << "\n";
    std::array<double, 5> doubleData = {3.14, 1.41, 2.71,  1.61, 1.73};
    quickSort(doubleData.begin(), doubleData.end());
    std::cout<< "Integer vector sorted: ";
    for (const auto& element : doubleData) {
        std::cout<< element << " ";
    }
    std::cout << "\n";
    return 0;
}
