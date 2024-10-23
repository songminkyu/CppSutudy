#include <iostream>
#include <type_traits>
#include <functional>

struct My_Weight_t {};
inline constexpr My_Weight_t my_weight;

struct My_Tall_t {};
inline constexpr My_Tall_t my_tall;

namespace std {
    template<>
    struct is_placeholder<My_Weight_t> : public integral_constant<int, 1> {};

    template<>
    struct is_placeholder<My_Tall_t> : public integral_constant<int, 2> {};
}

int BodyMass(int weight, int tall) {
    return weight + tall;
}

int main() {
    auto b = std::bind(BodyMass, my_weight, my_tall);
    std::cout << b(10, 11);
}