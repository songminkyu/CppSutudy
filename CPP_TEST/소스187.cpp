#include <utility> // index_sequence
#include <iostream> // std::cout
#include <type_traits> // std::is_same_v

void enumerate_pack(auto&& func, auto&&... args) {
    [&] <std::size_t... Idxs>(std::index_sequence<Idxs...>) {
        (std::forward<decltype(func)>(func)(Idxs,
            std::forward<decltype(args)>(args)), ...);
    }(std::make_index_sequence<sizeof...(args)>{});
}
void print_ints(auto&&... args) {
    enumerate_pack([](auto idx, auto&& arg) {
        if constexpr (std::is_same_v<std::remove_cvref_t<decltype(arg)>, int>) {
            std::cout << idx << ": " << arg << std::endl;
        }
        }, std::forward<decltype(args)>(args)...);
}
int main() { print_ints(1, 2, "buckle my shoe", 3, 4); }