#include <tuple> // std::apply
#include <iostream> // for demo only


/*
오늘의 귀여운 C ++ 트릭 : 튜플을 반복하기위한 더 나은 패턴

*/
void iterate_tuple(auto f, auto tuple) {
    std::apply([&](auto... args) {
        ((void)f(args), ...);
        }, tuple);
}
int main() {
    auto tup = std::make_tuple(42, "hello", 3.14);
    iterate_tuple([](auto arg) {
        std::cout << arg << std::endl;
        }, tup);
}