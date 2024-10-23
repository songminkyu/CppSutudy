#include <cstddef> // std::size_t
#include <utility> // std::forward
#include <limits> // std::numeric_limits
#include <type_traits> // std::integral_constant
#include <iostream> // demo purposes only
#include <sstream>  // demo purposes only

/*
* https://twitter.com/The_Whole_Daisy/status/1395750680011345922/photo/1
*/
constexpr size_t not_given = std::numeric_limits<size_t>::max();
template <size_t, size_t = not_given, size_t = 1, class = std::integral_constant<size_t, 0>>
struct slice;
template <size_t Begin, size_t End, size_t Stride, size_t I>
struct slice<Begin, End, Stride, std::integral_constant<size_t, I>> {
    static constexpr bool include = I >= Begin && I < End && ((I - Begin) % Stride == 0);
    using next = slice<Begin, End, Stride, std::integral_constant<size_t, I + 1>>;
    constexpr auto operator()(auto t, auto... ts) const {
        return [=](auto cb) {
            if (include) return next{}(ts...)([=](auto... sl) { return cb(t, sl...); });
            else return next{}(ts...)([=](auto... sl) { return cb(sl...); });
        };
    }
    constexpr auto operator()() const { return [](auto cb) { return cb(); }; }
};

int main() {
    auto print_pack = [](auto... p) { (std::cout << ... << p) << "\n"; };
    [&](auto... pack) {
        slice<3>{}(pack...)(print_pack); // prints "World42!"
        slice<1, 6, 2>{}(pack...)(print_pack); // prints "helloWorld!"
        slice<0, 3>{}(pack...)(print_pack); // prints "1hello3.14"
    }(1, "hello", 3.14, "World", 42, "!");
}