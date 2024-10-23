#include <utility>
#include <cstddef>

/*
Thanks to
@seanbax
 to putting out this challenge! Here's my best shot at 30 lines of readable C++17 code for the subset of mdspan functionality in their tweet (that they used Circle for): https://godbolt.org/z/PdxP5fe63

That said, Circle (http://circle-lang.org) is great. Check it out!

*/
// using size_t instead of ptrdiff_t to match @seanbax
template <size_t... Dim> struct extents { static constexpr auto rank = sizeof...(Dim); };

// Throw in generic over layout_left/layout_right as a bonus
template <class E, class, class = std::make_index_sequence<E::rank>> struct layout_impl;
template <size_t... Dim, class Layout, size_t... Idx>
struct layout_impl<extents<Dim...>, Layout, std::index_sequence<Idx...>> {
    static constexpr auto stride(int N) {
        // _idx_cond is Idx > N for layout_left, Idx < N for layout_right
        return (1 * ... * (Layout::_idx_cond(Idx, N) ? Dim : 1));
    }
};
struct layout_left {
    static constexpr bool _idx_cond(size_t Idx, size_t N) { return Idx > N; }
    template <class Extents> using mapping = layout_impl<Extents, layout_left>;
};
struct layout_right {
    static constexpr bool _idx_cond(size_t Idx, size_t N) { return Idx < N; }
    template <class Extents> using mapping = layout_impl<Extents, layout_left>;
};

template <class, class Exts, class Layout = layout_right,
    class = std::make_index_sequence<Exts::rank>>
    struct mdspan;

template <class ElementType, size_t... Dim, class Layout, size_t... Idx>
struct mdspan<ElementType, extents<Dim...>, Layout, std::index_sequence<Idx...>> {
    constexpr mdspan(ElementType(&array)[(1 * ... * Dim)]) : p(array) { }

    using mapping = typename Layout::template mapping<extents<Dim...>>;

    template <class... IndexType>
    constexpr ElementType& operator()(IndexType... index) {
        return p[(0 + ... + (index * mapping::stride(Idx)))];
    }

    ElementType* p;
};

template <int D0, int D1, int D2>
constexpr bool test() {
    int buffer[D0 * D1 * D2] = {};
    auto s = mdspan<int, extents<D0, D1, D2>>(buffer);
    int linear = 0;
    for (int i0 = 0; i0 < D0; ++i0)
        for (int i1 = 0; i1 < D1; ++i1)
            for (int i2 = 0; i2 < D2; ++i2)
                s(i0, i1, i2) = linear++;
    bool rv = true;
    for (int i = 0; i < D0 * D1 * D2; ++i) {
        rv = rv && buffer[i] == i;
    }
    return rv;
}

static_assert(test<2, 3, 4>());