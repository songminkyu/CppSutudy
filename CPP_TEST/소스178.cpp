#include <iostream>
#include <concepts>

int main() {
    auto fn = [](std::integral auto a)->std::integral auto {
        return a * 10;
    };
    std::integral auto v = fn(3);
    std::cout << v;
    return 0;
}