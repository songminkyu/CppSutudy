#include <iostream>

// How to do variadic template for even position in c++?

template <typename ... Ints>
constexpr bool check(Ints... args)  requires(std::is_same_v<std::common_type_t<Ints...>, int> && sizeof... (Ints) % 2 == 0)
{
    int arr[]{ args... };
    for (size_t i{}; i < sizeof... (args) / 2; ++i) {
        if (!(arr[2 * i] < arr[2 * i + 1])) return false;
    }
    return true;
}

template <typename Int, typename ... Ints>
constexpr bool recursive_version_check(Int int1, Int int2, Ints... ints)requires(std::is_same_v<std::common_type_t<Int, Ints...>, int> && sizeof... (Ints) % 2 == 0)
{
    if constexpr (sizeof... (Ints) == 0) return int1 < int2;
    else return int1 < int2 && (check(ints...));
}


int main()
{
    std::cout << check(1, 3, 5, 7, 9, 11) << std::endl;

    std::cout << recursive_version_check(4, 3, 7, 9, 2, 4);
}