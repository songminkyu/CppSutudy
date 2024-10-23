#include <cstdint>
#include <limits>
#include <numeric>
#include <iostream>

int main()
{
    std::uint32_t a = std::numeric_limits<std::uint32_t>::max();
    std::uint32_t b = std::numeric_limits<std::uint32_t>::max() - 2;

    std::cout << "a: " << a << '\n'
        << "b: " << b << '\n'
        << "Incorrect (overflow and wrapping): " << (a + b) / 2 << '\n'
        << "Correct: " << std::midpoint(a, b) << "\n\n";


    auto on_pointers = [](int i, int j) {
        char const* text = "0123456789";
        char const* p = text + i;
        char const* q = text + j;
        std::cout << "std::midpoint('" << *p << "', '" << *q << "'): '"
            << *std::midpoint(p, q) << "'\n";
    };

    on_pointers(2, 4);
    on_pointers(2, 5);
    on_pointers(5, 2);
    on_pointers(2, 6);

     for (auto v: {0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0}) {
        std::cout << "std::lerp(10, 20, " << v << "): " << std::lerp(10, 20, v) << std::endl;
    }
}