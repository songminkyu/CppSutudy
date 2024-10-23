#include <iostream>
#include <utility>
#include <tuple>
#include <array>

int main() {
    std::tuple         m1{ 1,"two",3.1f };
    std::array<int, 3> m2{ 4,5,6 };
    std::pair          m3{ 7,8 };

    auto cats = std::tuple_cat(m1, m2, m3);
    std::cout << get<3>(cats) << std::endl;
    std::cout << get<6>(cats) << std::endl;
}
