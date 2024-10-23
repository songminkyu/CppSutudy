#include <type_traits> // type_identity, just for preventing decays and such

//C랭에서만 가능한코드.... 

/*
Cute C++ trick of the day (Template Meta Thursday): I've been trying to write a simple meta-bubble sort 
with fold expressions for a while. The key: do the inner iterations backwards, since `T, Ts...` is an 
allowed partial specializaton but `Ts..., T` isn't
https://godbolt.org/z/onhbP1Yhe
*/

template <class...> struct type_list; // for expressing the result
template <template <class, class> class Less, class... Ts> struct inner {};
template <template <class, class> class Less, class... Ts> struct outer;
template <template <class, class> class Less, class T, class... Ts>
struct inner<Less, T, Ts...> {
    static auto next_iteration()->outer<Less, T, Ts...>;
    // if U is "less" than T according to the comparator, swap T and U
    template <class U> requires Less<T, U>::value
        friend auto operator+(std::type_identity<U>, inner)->inner<Less, T, U, Ts...>;
    template <class U> // otherwise, just insert U
    friend auto operator+(std::type_identity<U>, inner)->inner<Less, U, T, Ts...>;
};
// Base case, just insert U
template <template <class, class> class Less, class U>
auto operator+(std::type_identity<U>, inner<Less>)->inner<Less, U>;
// outer iterations fold basically just for counting the number of iterations 
template <template <class, class> class Less, class... Ts>
struct outer {
    static auto result()->type_list<Ts...>;
    template <class U> auto operator=(std::type_identity<U>) {
        return (std::type_identity<Ts>{} + ... + inner<Less>{}).next_iteration();
    }
};
template <template <class, class> class Less, class... Ts> using sort_types =
decltype((outer<Less, Ts...>{} = ... = std::type_identity<Ts>{}).result());

// Demo of the sort_types in action
template <int I> struct i; // for readability; shorter that writing std::integral_constant
template <class, class> struct IntLess;
template <int I, int J> struct IntLess<i<I>, i<J>> : std::bool_constant<(I < J)> {};
static_assert(
    std::is_same_v<
    sort_types<IntLess, i<3>, i<1>, i<4>, i<1>, i<5>, i<9>, i<2>, i<6>>,
    type_list<i<1>, i<1>, i<2>, i<3>, i<4>, i<5>, i<6>, i<9>>
    >
    );

// This is how I go about debugging something like this, for anyone who is interested
#define DEBUG 0
#if DEBUG
template <class...> struct type_display; // undefined class template makes the compiler display the type
// first inner
type_display<decltype(std::type_identity<i<5>>{} + inner<IntLess, type_list<>>{}) > i{};
// first outer iteration
type_display<decltype(outer<IntLess, i<3>, i<1>, i<4>, i<1>, i<5>>{} = std::type_identity</*doesn't matter*/int>{}) > o{};
// second outer iteration
type_display<decltype((outer<IntLess, i<3>, i<1>, i<4>, i<1>, i<5>>{} = std::type_identity<int>{}) = std::type_identity<int>{}) > o{};
// full sort
type_display<sort_types<IntLess, i<3>, i<1>, i<4>, i<1>, i<5>>> t{};
#endif
