#include <iostream>
template <class... Ts>
void print_args_backwards(Ts... ts) {
    auto print_one = [](auto t) {
        std::cout << t << ' ';
        // Anything with a reasonable assignment operator will work here
        return std::type_identity<void>{};
    };
    // Backwards:
    (print_one(ts) = ...); std::cout << '\n';
    // Forwards:
    (print_one(ts), ...); std::cout << '\n';
}
int main() {
    print_args_backwards(1, 2, "hello", 3, 4, "world");
}