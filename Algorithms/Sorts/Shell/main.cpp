#include <iostream>
#include <vector>
#include <array>

template <typename Iterator>
void shellSort(Iterator begin, Iterator end) {
    auto n = std::distance(begin, end);

    for (auto gap = n / 2; gap > 0; gap /= 2) {
        for (auto i = gap; i < n; i++) {
            auto temp = *(begin + i);
            int j;
            for (j = i; j >= gap && *(begin + (j - gap)) > temp; j -= gap) {
                *(begin + j) = *(begin + (j - gap));
            }
            *(begin + j) = temp;
        }
    }
}

auto main() -> int {
    std::vector<int> intVecData = {3, 34, 34, 1, 5, 7, 8, 2, 56, 4, 9};
    shellSort(intVecData.begin(), intVecData.end());
    std::cout<< "Double vector sorted: ";
    for (const auto& element : intVecData) {
        std::cout << element << " ";
    }
    std::cout << "\n";

    std::vector<double> doubleVecData = {3.14, 1.41, 2.71,  1.61, 1.73};
    shellSort(doubleVecData.begin(), doubleVecData.end());
    std::cout<< "Double vector sorted: ";
    for (const auto& element : doubleVecData) {
        std::cout << element << " ";
    }
    std::cout << "\n";

    std::array<int, 5> intData = {3, 34, 34, 1, 5};
    shellSort(intData.begin(), intData.end());
    std::cout<< "Integer array sorted: ";
    for (const auto& element: intData) {
        std::cout<< element << " ";
    }
    std::cout << "\n";
    std::array<double, 5> doubleData = {3.14, 1.41, 2.71,  1.61, 1.73};
    shellSort(doubleData.begin(), doubleData.end());
    std::cout<< "Integer vector sorted: ";
    for (const auto& element : doubleData) {
        std::cout<< element << " ";
    }
    std::cout << "\n";
    return 0;
}
