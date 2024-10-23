#include <iostream>
namespace NS {
    template<auto s, auto e>
    struct A { };

    template<auto s>
    struct AIter {
        std::size_t start = s;
        decltype(auto) operator++() noexcept { start++; return *this; }
        auto operator*() noexcept { return start; }
    };

    template<auto s, auto e>
    auto begin(A<s, e>) noexcept { return AIter<s>{}; }

    template<auto s, auto e>
    auto end(A<s, e>) noexcept { return e; }

    template<auto s>
    auto operator!=(const AIter<s>& v, const decltype(s)& e) noexcept { return v.start != e; }
}


int main() {
    int m = 0;
    for (auto item : NS::A<1, 10>{}) {
        m += item;
    }
    
    std::cout << m << "\n";

}
