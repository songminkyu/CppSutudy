
#include <iostream>
#include <tuple>
#include <functional>
#include <type_traits>

/*
for_each2
for_each2 is an extended version of for_each, that takes two tuples in input, and a function that takes two elements:
*/

//사족 코드가 많이 들어간 C++20 의 이전 코드 즉 C++17 코드는 사족이 너무 많다...

template<class F, class...Args>
constexpr F for_each_arg(F f, Args&&...args) {
    std::initializer_list<int>{((void)f(std::forward<Args>(args)), 0)...};
    return f;
}

template <class Tuple, class F>
constexpr F for_each(Tuple&& t, F&& f)
{
    return for_each_impl(std::forward<Tuple>(t), std::forward<F>(f),
        std::make_index_sequence<std::tuple_size<std::remove_reference_t<Tuple>>::value>{});
}

template <class Tuple, class F, std::size_t... I>
constexpr F for_each_impl(Tuple&& t, F&& f, std::index_sequence<I...>)
{
    return (void)std::initializer_list<int>{(std::forward<F>(f)(std::get<I>(std::forward<Tuple>(t))), 0)...}, f;
}

template <class Tuple1, class Tuple2, class F, std::size_t... I>
F for_each2_impl(Tuple1&& t1, Tuple2&& t2, F&& f, std::index_sequence<I...>)
{
    return (void)std::initializer_list<int>{(std::forward<F>(f)(std::get<I>(std::forward<Tuple1>(t1)), std::get<I>(std::forward<Tuple2>(t2))), 0)...}, f;
}

template <class Tuple1, class Tuple2, class F>
constexpr decltype(auto) for_each2(Tuple1&& t1, Tuple2&& t2, F&& f)
{
    return for_each2_impl(std::forward<Tuple1>(t1), std::forward<Tuple2>(t2), std::forward<F>(f),
        std::make_index_sequence<std::tuple_size<std::remove_reference_t<Tuple1>>::value>{});
}

template <typename Fn, typename Argument, std::size_t... Ns>
auto tuple_transform_impl(Fn&& fn, Argument&& argument, std::index_sequence<Ns...>) {
    if constexpr (sizeof...(Ns) == 0) return std::tuple<>(); // empty tuple
    else if constexpr (std::is_same_v<decltype(fn(std::get<0>(argument))), void>) {
        (fn(std::get<Ns>(argument)), ...); // no return value expected
        return;
    }
    // then dispatch lvalue, rvalue ref, temporary
    else if constexpr (std::is_lvalue_reference_v<decltype(fn(std::get<0>(argument)))>) {
        return std::tie(fn(std::get<Ns>(argument))...);
    }
    else if constexpr (std::is_rvalue_reference_v<decltype(fn(std::get<0>(argument)))>) {
        return std::forward_as_tuple(fn(std::get<Ns>(argument))...);
    }
    else {
        return std::tuple(fn(std::get<Ns>(argument))...);
    }
}

template <typename Fn, typename... Ts>
auto tuple_transform(Fn&& fn, const std::tuple<Ts...>& tuple) {
    return tuple_transform_impl(std::forward<Fn>(fn), tuple,
        std::make_index_sequence<sizeof...(Ts)>());
}


template<typename Tuple, typename Predicate>
constexpr size_t find_if(Tuple&& tuple, Predicate pred)
{

    /*
    사용법    
    constexpr auto myTuple = std::make_tuple(1, 2, 3);
    constexpr auto firstEvenIndex = find_if(myTuple, [](int n){ return n % 2 == 0; });
    std::cout << std::get<firstEvenIndex>(myTuple) << '\n';    
    */
    size_t index = std::tuple_size<std::remove_reference_t<Tuple>>::value;
    size_t currentIndex = 0;
    bool found = false;
    for_each(tuple, [&](auto&& value)
        {
            if (!found && pred(value))
            {
                index = currentIndex;
                found = true;
            }
            ++currentIndex;
        });
    return index;
}

template<typename Tuple, typename Action>
void perform(Tuple&& tuple, size_t index, Action action)
{
    size_t currentIndex = 0;
    for_each(tuple, [action = std::move(action), index, &currentIndex](auto&& value)
    {
        if (currentIndex == index)
        {
            action(std::forward<decltype(value)>(value));
        }
        ++currentIndex;
    });
}

template<typename Tuple, typename Predicate>
bool all_of(Tuple&& tuple, Predicate pred)
{
    return find_if(tuple, std::not_fn(pred)) == std::tuple_size<std::decay_t<Tuple>>::value;
}

template<typename Tuple, typename Predicate>
bool none_of(Tuple&& tuple, Predicate pred)
{
    return find_if(tuple, pred) == std::tuple_size<std::decay_t<Tuple>>::value;
}

template<typename Tuple, typename Predicate>
bool any_of(Tuple&& tuple, Predicate pred)
{
    return !none_of(tuple, pred);
}


int main()
{
    auto tuple1 = std::make_tuple(1, std::string{ "two" });
    auto tuple2 = std::make_tuple(std::string{ "one" }, 2);

    for_each2(tuple1, tuple2, [](auto&& i, auto&& s) { std::cout << i << '-' << s << '\n'; });

    auto tuple3 = std::make_tuple(1,2,3,4,5);
    auto r = tuple_transform([](auto i) {return i * 2; }, tuple3);
    std::cout << std::get<2>(r) << std::endl;
  
}
