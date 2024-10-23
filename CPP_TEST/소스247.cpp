#include <iostream>
#include <string>
#include <string_view>
#include <tuple>
#include <utility>

template<class... Args>
void print(std::string_view cmt, std::tuple<Args...>& p) {
    [&] <class T, T... idxs>(std::integer_sequence<T, idxs...>) {
        std::cout << cmt << '[';
        ((std::cout << std::get<idxs>(p) << ","), ...);
        std::cout << "]\n";
    }(std::make_integer_sequence<std::size_t, sizeof...(Args)>{});
}

int main() {
    using namespace std::literals;

    std::tuple a{ "test1"s,"test2"s };
    std::tuple b{ "test3"s,"test4"s };
    auto p = std::tuple_cat(std::move(a), b);
    print("a:", a);
    print("b:", b);
    print("p:", p);
}