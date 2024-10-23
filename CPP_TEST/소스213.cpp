#include <utility> // std::type_identity

//Äü Á¤·Ä

template <class...> class lst; // never instantiated
template <class... F> struct overloads : F... { using F::operator()...; };
template <class... F> overloads(F...)->overloads<F...>;
template <class, template <class...> class> struct sort;
template <template <class...> class, class, class, class> struct join;
template <template <class...> class C, class P, class... Ts, class... Us>

struct join<C, P, lst<Ts...>, lst<Us...>> {
    using joined = lst<Ts..., P, Us...>;
    using type = typename join<C, P, typename sort<lst<Ts...>, C>::type,
        typename sort<lst<Us...>, C>::type>::joined;
    template <class... Vs, class... Ws>
    join<C, P, lst<Ts..., Vs...>, lst<Us..., Ws...>>
        operator=(join<C, P, lst<Vs...>, lst<Ws...>>);
};
template <class U, class T, template <class...> class Cmp>
concept ComparesLess = Cmp<typename U::type, T>::value;
template <class... T, template <class...> class C> requires (sizeof...(T) <= 1)
struct sort<lst<T...>, C> { using type = lst<T...>; };
template <class T, class... Ts, template <class...> class Cmp>
struct sort<lst<T, Ts...>, Cmp> : decltype((overloads{
    [](ComparesLess<T, Cmp> auto u)
      -> join<Cmp, T, lst<typename decltype(u)::type>, lst<>> {},
    [](auto u) -> join<Cmp, T, lst<>, lst<typename decltype(u)::type>> {}
    }(std::type_identity<Ts>{}) = ... = join<Cmp, T, lst<>, lst<>>{})) {};
    // Example usage: 
#include <type_traits>
    template <int I> struct int_;
    template <class, class> struct type_less;
    template <int I, int J> struct type_less<int_<I>, int_<J>>
: std::bool_constant<(I < J)> { };

#if true
static_assert(
    std::is_same_v<
    typename sort<lst<int_<4>, int_<5>, int_<4>, int_<7>, int_<1>>, type_less>::type,
    lst<int_<1>, int_<4>, int_<4>, int_<5>, int_<7>>>);
#endif

int main()
{
#if false
    static_assert(
        std::is_same_v<
        typename sort<lst<int_<4>, int_<5>, int_<4>, int_<7>, int_<1>>, type_less>::type,
        lst<int_<1>, int_<4>, int_<4>, int_<5>, int_<7>>>);
#endif
}