/*
    As of today, May 31, 2020, only GNU g++ version 10.1 supports C++20 ranges library

    g++ -std=c++20 ranges.cpp -ltbb -o g.exe
*/


#include <range/v3/view/filter.hpp>
#include <range/v3/view/transform.hpp> // for G++20 ranges library, MSVC and clang++ does not yet support ranges library
#include <iostream>


void test_range_views_filter()
{
    std::vector container{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    std::cout << "Ranges in action" << std::endl;

    for (auto&& i : container)
    {
        std::cout << i << ", ";
    }
    std::cout << "\n";

    // the type of i is forwarding reference
    auto even = []<typename T>(T && i) // template parameter for lambda was introduced to C++20 Core Language.
    {
        return !(i % 2);
    };

    // the type of i is forwarding reference
    auto odd = [](auto&& i)
    {
        return i % 2; // odd number
    };

    // the type of i is forwarding reference
    auto square = [](auto&& i)
    {
        return i * i;
    };

    std::cout << "Ranges in action" << std::endl;

    // what will be the type of i
    for (auto&& i : container)
    {
        std::cout << "type of i: " << typeid(decltype(i)).name() << std::endl;

        std::cout << i << ", ";
    }
    std::cout << "\n";

    // what will be the type of j
    for (auto&& j : { 2, 3, 5, 7, 11 })
    {
        std::cout << "type of j: " << typeid(decltype(j)).name() << std::endl;

        std::cout << j << ", ";
    }
    std::cout << "\n";

    // whenever your algorithm does not work as expected or predicted,
    // double-check the type of the variable using Tpf_GetTypeCategory

    std::cout << "Ranges in action - filter even numbers" << std::endl;
    for (auto&& i : container | ranges::views::filter(even))
    {
        std::cout << i << ", ";
    }

    std::cout << "\n";

    std::cout << "Ranges in action - filter odd numbers" << std::endl;
    for (auto&& i : container | ranges::views::filter(odd))
    {
        std::cout << i << ", ";
    }

    std::cout << "\n";

    //////////////////////////
    std::cout << "Ranges in action - filter even numbers and square" << std::endl;
    for (auto&& i : container | ranges::views::filter(even) | ranges::views::transform(square))
    {
        std::cout << i << ", ";
    }

    std::cout << "\n";

    std::cout << "Ranges in action - filter odd numbers and square" << std::endl;
    for (auto&& i : container | ranges::views::filter(odd) | ranges::views::transform(square))
    {
        std::cout << i << ", ";
    }

    std::cout << "\n";

}

int main()
{
    test_range_views_filter();
}
