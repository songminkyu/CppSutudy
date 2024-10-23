#include <iostream>
#include <vector>
#include <Ranges_v3/range/v3/all.hpp>

int main(int argc, char* argv[])
{
    const std::vector<int> v1{ 0,1,2,3,4,5 };
    const char v2[]={ 'a','b','c','d','e','f' };

    auto rng = ranges::views::zip(v2, v1);

    for (auto&& [first, second] : rng) {
        std::cout << first << ", " << second << '\n';
    }
          
    return 0;
}