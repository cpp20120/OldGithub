#include "sort.hpp"
#include <fmt/core.h>
#include <fmt/ranges.h>

auto main() -> int {
    constexpr std::array<int, 10> arr = {170, 45, 75, 90, 802, 24, 2, 66, 134, 11};
    constexpr auto sortedArr = [&]() constexpr {
        auto a = arr;
        radixSort(a);
        return a;
    }();

    static_assert(sortedArr == std::array<int, 10>{2, 11, 24, 45, 66, 75, 90, 134, 170, 802}, "Array is not sorted correctly!");
    fmt::print("{}", sortedArr);
    return 0;
}