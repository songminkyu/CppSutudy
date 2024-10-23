// A sample standard C++20 program that prints
// the first N Pythagorean triples.
#include <iostream>
#include <optional>
#include <ranges>   // New header!

using namespace std;

// maybe_view defines a view over zero or one
// objects.
template <semiregular T>
struct maybe_view : ranges::view_interface<maybe_view<T>> {
    maybe_view() = default;
    maybe_view(T t) : data_(move(t)) {
    }
    T const* begin() const noexcept {
        return data_ ? &*data_ : nullptr;
    }
    T const* end() const noexcept {
        return data_ ? &*data_ + 1 : nullptr;
    }
private:
    optional<T> data_{};
};

// "for_each" creates a new view by applying a
// transformation to each element in an input
// range, and flattening the resulting range of
// ranges.
// (This uses one syntax for constrained lambdas
// in C++20.)
inline constexpr auto for_each =
[]<ranges::range R,
    typename Fun,                                                        // 이 부분은 원 코드와 다름
    random_access_iterator I = ranges::iterator_t<R>>(R && r, Fun fun)   // 이 부분은 원 코드와 다름
    requires ranges::range<indirect_result_t<Fun, I>> {
    return forward<R>(r)
        | views::transform(move(fun))
        | views::join;
};

// "yield_if" takes a bool and a value and
// returns a view of zero or one elements.
inline constexpr auto yield_if =
[] <semiregular T>(bool b, T x) {
    return b ? maybe_view{ std::move(x) }
    : maybe_view<T>{};
};

int main() {
    // "yield_if" takes a bool and a value and
    // returns a view of zero or one elements.
    using views::iota;
    auto triples =
        for_each(iota(1), [](int z) {
        return for_each(views::iota(1, z + 1), [=](int x) {
            return for_each(views::iota(x, z + 1), [=](int y) {
                return yield_if(x * x + y * y == z * z, make_tuple(x, y, z));
                });
            });
            });

    // Display the first 10 triples
    for (auto triple : triples | views::take(10))
        cout << '('
        << get<0>(triple) << ','
        << get<1>(triple) << ','
        << get<2>(triple) << ')' << '\n';

    return 0;
}