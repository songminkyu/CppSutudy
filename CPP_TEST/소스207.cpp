#include <utility> // std::forward
#include <iostream> // for example usage only
auto parameter_pack_product(auto... ts) {
    return [=](auto... us) {
        return [=](auto func) {
            ([&](auto t) {
                ([&](auto u) { func(t, u); }(us), ...);
                }(ts), ...);
        };
    };
}
int main() {
    parameter_pack_product(1, 2, 3)("hello", "world")(
        [](auto t, auto u) {
            std::cout << t << ", " << u << std::endl;
        }
    );
}