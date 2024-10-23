#include <ranges> // range, range_reference_t
#include <variant> // varaint, visit
#include <utility> // make_index_sequence, index_sequence
#include <tuple> // tuple, get
#include <vector> // for demo purposes only
#include <string_view> // for demo purposes only
#include <iostream> // for demo purposes only

template <class T, class F>
concept visitable = requires(T & t, F & f) { std::visit(f, t); };
template <class T> requires requires{ std::tuple_size<T>::value; }
auto safe_index_sequence() { return std::make_index_sequence<std::tuple_size_v<T>>{}; };
template <class T> int safe_index_sequence();
template <class T, class F, class I = decltype(safe_index_sequence<T>())>
concept my_iterable_tuple = requires(I i, T & t, F & f) {
    [] <std::size_t... Idxs>(std::index_sequence<Idxs...>, auto & tt, auto & ff) {
        (ff(std::get<Idxs>(tt)), ...);
    }(i, t, f);
};
template <class F, std::ranges::range R>
requires visitable<std::ranges::range_reference_t<R>, F>
void loop_over_whatever(R r, F f) {
    for (auto& v : r) { std::visit(f, v); }
}
template <class F, my_iterable_tuple<F> T>
void loop_over_whatever(T t, F f) {
    [&] <std::size_t... Idxs>(std::index_sequence<Idxs...>) {
        (f(std::get<Idxs>(t)), ...);
    }(std::make_index_sequence<std::tuple_size_v<T>>{});
}
int main() {
    std::vector<std::variant<int, std::string_view, double>> vec = { 42, "hello", 3.14 };
    std::tuple<int, std::string_view, double> tup = { 42, "hello", 3.14 };
    loop_over_whatever(vec, [](auto const& val) { std::cout << val << std::endl; });
    loop_over_whatever(tup, [](auto const& val) { std::cout << val << std::endl; });
}