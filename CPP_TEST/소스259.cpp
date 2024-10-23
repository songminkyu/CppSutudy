#include <tuple>
#include <array>
#include <utility>

namespace details
{
    template <typename Tuple, typename Mapping>
    struct return_type;

    template <template <typename ...> typename Tuple, typename ... Types, typename Mapping>
    struct return_type<Tuple<Types...>, Mapping>
    {
        using type = Tuple<std::invoke_result_t<Mapping, Types>...>;
    };
    template <template <typename, std::size_t> typename Array,
        typename T, std::size_t Size, typename Mapping>
        struct return_type<Array<T, Size>, Mapping>
    {
        using type = Array<std::invoke_result_t<Mapping, T>, Size>;
    };

    template <typename Tuple, typename Mapping>
    using return_type_t = typename return_type<Tuple, Mapping>::type;

    template <typename Tuple, typename Mapping, std::size_t ... Indices>
    return_type_t<std::decay_t<Tuple>,
        std::decay_t<Mapping>> perform_mapping(Tuple&& tup,
            Mapping&& mapping,
            std::index_sequence<Indices...>)
    {
        return { mapping(std::get<Indices>(std::forward<Tuple>(tup)))... };
    }
}

template <typename Tuple, typename Mapping,
    std::size_t Size = std::tuple_size<std::decay_t<Tuple>>::value>
    auto perform_mapping(Tuple&& tup, Mapping&& mapping)
{
    return details::perform_mapping(std::forward<Tuple>(tup),
        std::forward<Mapping>(mapping), std::make_index_sequence<Size>{});
}

#include <algorithm>
#include <iterator>
#include <iostream>
#include <string>

int main()
{
    auto mapper = [](int x) {return x * 2; };
    std::array<int, 3> a{ 1, 2, 3 };
    auto b = perform_mapping(a, mapper);

    std::copy(b.begin(), b.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';

    auto tuple = std::make_tuple(1, std::string{ "a" });
    auto self_adder = [](const auto& x) {return x + x; };
    auto another_tuple = perform_mapping(tuple, self_adder);
    std::cout << std::get<0>(another_tuple) << ' ' << std::get<1>(another_tuple) << '\n';
}