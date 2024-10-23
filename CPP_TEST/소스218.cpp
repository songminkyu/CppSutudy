#include <utility> // std::type_identity

//메타 버블 정렬
template <class...> class lst; // never instantiated
template <template <class...> class, class, class, class, int, int> struct impl;
template <template <class...> class Cmp, class T, class... Ts,
    class U, class... Us, int I, int N> requires (Cmp<T, U>::value)
    struct impl<Cmp, lst<Ts...>, T, lst<U, Us...>, I, N>
    : impl<Cmp, lst<Ts..., T>, U, lst<Us...>, I, N> {};
template <template <class...> class Cmp, class T, class... Ts,
    class U, class... Us, int I, int N>
    struct impl<Cmp, lst<Ts...>, T, lst<U, Us...>, I, N>
    : impl<Cmp, lst<Ts..., U>, T, lst<Us...>, I, N> {};
template <template <class...> class Cmp, class T, class... Ts, class U, int I, int N>
requires (I != N)
struct impl<Cmp, lst<T, Ts...>, U, lst<>, I, N>
    : impl<Cmp, lst<>, T, lst<Ts..., U>, I + 1, N> {};
template <template <class...> class Cmp, class... Ts, class U, int N>
struct impl<Cmp, lst<Ts...>, U, lst<>, N, N>
    : std::type_identity<lst<Ts..., U>> {};
template <class, template <class...> class> struct sort;
template <class T, class... Ts, template <class...> class Cmp>
struct sort<lst<T, Ts...>, Cmp> : impl<
    Cmp, lst<>, T, lst<Ts...>, 0, sizeof...(Ts)> { };
// Example usage:
template <int I> struct int_;
template <class, class> struct type_less;
template <int I, int J> struct type_less<int_<I>, int_<J>>
    : std::bool_constant<(I < J)> { };
    static_assert(
        std::is_same_v<
        typename sort<lst<int_<4>, int_<5>, int_<4>, int_<7>, int_<1>>, type_less>::type,
        lst<int_<1>, int_<4>, int_<4>, int_<5>, int_<7>>>);