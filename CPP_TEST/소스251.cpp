#include <iostream>
#include <tuple>

//C++20 부터 가능
template <class Tuple, class F>
constexpr decltype(auto) for_each(Tuple&& tuple, F&& f)
{
    return [] <std::size_t... I>
        (Tuple && tuple, F && f, std::index_sequence<I...>)
    {
        (f(std::get<I>(tuple)), ...);
        return f;
    }(std::forward<Tuple>(tuple), std::forward<F>(f),
        std::make_index_sequence<std::tuple_size<std::remove_reference_t<Tuple>>::value>{});
}

int main()
{
    auto myTuple = std::make_tuple(1, 2, 3);
    for_each(myTuple, [](int& n) {std::cout << n * 2 << '\n'; });
}