#include <array>
#include <iostream>

namespace detail {

    template <class T, std::size_t N, std::size_t... I>
    constexpr std::array<std::remove_cv_t<T>, N>
        to_array_impl(T(&& a)[N], std::index_sequence<I...>)
    {
        return { {std::move(a[I])...} };
    }
    template <class T, std::size_t N, std::size_t... I>
    constexpr std::array<std::remove_cv_t<T>, N>
        to_array_impl(T(&a)[N], std::index_sequence<I...>)
    {
        return { {a[I]...} };
    }
}

template <class T, std::size_t N>
constexpr std::array<std::remove_cv_t<T>, N> to_array(T(&& a)[N])
{
    return detail::to_array_impl(std::move(a), std::make_index_sequence<N>{});
}
template <class T, std::size_t N>
constexpr std::array<std::remove_cv_t<T>, N> to_array(T(&a)[N])
{
    return detail::to_array_impl(a, std::make_index_sequence<N>{});
}


int main()
{
    auto a1 = to_array("foo");
    static_assert(a1.size() == 4);

    // deduces both element type and length
    auto a2 = to_array({ 0, 2, 1, 3 });
    static_assert(std::is_same_v<decltype(a2), std::array<int, 4>>);

    // deduces length with element type specified
    // implicit conversion happens
    auto a3 = to_array<long, 3>({ 0, 1, 3 });
    static_assert(std::is_same_v<decltype(a3), std::array<long, 3>>);

    std::cout << a3[2] << std::endl;

    auto a4 = to_array<std::pair<int, float>>(
        { { 3, .0f }, { 4, .1f }, { 4, .1e23f } });
    static_assert(a4.size() == 3);

    // creates a non-copyable std::array
    auto a5 = to_array({ std::make_unique<int>(3) });
    static_assert(a5.size() == 1);

}