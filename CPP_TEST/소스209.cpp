#include <cstddef>
#include <type_traits>
#include <utility>
#include <iostream>

//https://twitter.com/The_Whole_Daisy?fbclid=IwAR2hI-gd3rhfJwfip_tey6kIkQEsH7fwlCbSNI1CAXY30dlEQ7_zTDy2Rh0

//clang에서만 컴파일 가능.
constexpr inline auto make_my_tuple = [](auto &&...ts) {
    return [...ts = decltype(ts)(ts)] (auto f) { return f(ts...); };
};

template<typename, std::size_t> concept Any = true;
template<std::size_t N> constexpr auto get = [](auto &&lambda) -> decltype(auto) {
    return [&]<std::size_t ...I>(std::index_sequence<I...>) -> decltype(auto) {
        return lambda([](Any<I> auto &..., auto &v, auto &...) -> decltype(auto) {
            if constexpr (std::is_rvalue_reference_v<decltype(lambda)>)
                return std::move(v);
            else
                return v;
        });
    }(std::make_index_sequence<N>());
};

int main() {
  	auto t = make_my_tuple(42, "hello", 3.14, "world");
  	std::cout << get<1>(t) << " " << get<3>(t) << std::endl;
}