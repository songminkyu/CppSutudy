
#include <iostream>
#include <concepts>
/*
Cute C++ trick of the day: as a response to several comments on my previous trick,
here's how you'd use the associativity imposed by the fold expression itself to control
the order of iteration over a parameter pack with a fold expression
*/
// https://godbolt.org/z/hn5Y8ebeE
//왜 안되지???

template <class T> struct iterate_backwards {
    T& value;
    // We can use just about any operator here; pipe is just a common choice
    friend auto operator|(iterate_backwards v, std::invocable<T> auto f) {
        f(v.value);
        return f;
    }
};
template <class T> iterate_backwards(T&)->iterate_backwards<T>;
template <class T> struct iterate_forwards {
    T& value;
    friend auto operator|(std::invocable<T> auto f, iterate_forwards v) {
        f(v.value);
        return f;
    }
};
template <class T> iterate_forwards(T&)->iterate_forwards<T>;
void print_args(auto... args) {
    // backwards:
    (iterate_backwards{ args } | ... | [](auto t) { std::cout << t << "\n"; });
    // forwards:
    ([](auto t) { std::cout << t << "\n"; } | ... | iterate_forwards{ args });
}
int main() {
    print_args(1, 2, "hello", 3, 4, "world");
}