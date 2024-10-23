#include <iostream>
#include "tcb/span.hpp"

using static_span_t = tcb::span<int, 3>;
using dynamic_span_t = tcb::span<int>;

static_assert(std::tuple_size_v<static_span_t> == static_span_t::extent);
static_assert(!tcb::detail::is_complete<std::tuple_size<dynamic_span_t>>::value);

int main()
{
    // C++, why you no let me do constexpr structured bindings?

    int arr[] = { 1, 2, 3 };

    auto& [a1, a2, a3] = arr;
    auto&& [s1, s2, s3] = tcb::make_span(arr);


    std::cout << (a1 == s1);
    std::cout << std::endl;
    std::cout << (a2 == s2);
    std::cout << std::endl;
    std::cout << (a3 == s3);
    std::cout << std::endl;

    a1 = 99;    
    std::cout << (s1 == 99);
    std::cout << std::endl;
    s2 = 100;
    std::cout << (a2 == 100);


}