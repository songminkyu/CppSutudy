#include <array>

constexpr auto scan(auto... ts) {
    auto rv = std::array{ ts... };
    for (auto i = 0; i < sizeof...(ts); ++i) {
        if (i > 0) rv[i] += rv[i - 1];
    }
    return rv;
}


int main()
{
    static_assert(
        scan(1, 2, 3, 4, 5) == std::array{ 1, 3, 6, 10, 15 }
    );
}