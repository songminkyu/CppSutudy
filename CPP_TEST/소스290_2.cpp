
/*
Cute C++ trick of the day (Template Meta Thursday): fold-based meta-programming can make fairly complex meta-programs surprisingly readable. 
Here's quicksort in 25 lines. I like this example because it clearly uses overloads as what they are: patterns. https://godbolt.org/z/q17EfszY9

CLang 에서만 가능한 코드

*/

#include <type_traits> // type_identity, just for preventing decays and such
template <class...> struct type_list {};
template <class, class> struct Less; // type-wise comparator, customizable
template <class, class = type_list<>, class = type_list<>> struct partition; // fwd decl
template <class... Ts, class... Us> // join type lists with operator+
auto operator+(type_list<Ts...>, type_list<Us...>)->type_list<Ts..., Us...>;
// We can use the unspecialized template as the base case
template <class... Ts> struct quick_sort { static auto result()->type_list<Ts...>; };
template <class Pivot, class... Ts> struct quick_sort<Pivot, Ts...> {
    // quicksort is just partition and (trivial) join, done recursively, so:
    auto result() { return (partition<Pivot>{} = ... = std::type_identity<Ts>{}).join(); }
};
template <class... Ts> using sort = decltype(quick_sort<Ts...>{}.result());
// Partition into greater that pivot and less than pivot
template <class Pivot, class... Ls, class... Rs>
struct partition<Pivot, type_list<Ls...>, type_list<Rs...>> {
    // join the results using the type_list operator+ we defined earlier
    static auto join() { return sort<Ls...>{} + type_list<Pivot>{} + sort<Rs...>{}; }
    // if U is "less" than Pivot, put it in the left list
    template <class U> requires Less<U, Pivot>::value
        auto operator=(std::type_identity<U>)
        ->partition<Pivot, type_list<Ls..., U>, type_list<Rs...>>;
    template <class U> // otherwise, put it in the right list
    auto operator=(std::type_identity<U>)
        ->partition<Pivot, type_list<Ls...>, type_list<Rs..., U>>;
};

// Demo of the sort_types in action
template <int I> struct i; // for readability; shorter that writing std::integral_constant
template <int I, int J> struct Less<i<I>, i<J>> : std::bool_constant<(I < J)> {};
static_assert(
    std::is_same_v<
    sort<i<3>, i<1>, i<4>, i<1>, i<5>, i<9>, i<2>, i<6>>,
    type_list<i<1>, i<1>, i<2>, i<3>, i<4>, i<5>, i<6>, i<9>>
    >
    );

void main()
{
    sort<i<3>, i<1>, i<4>, i<1>, i<5>, i<9>, i<2>, i<6>> s{};
    

}