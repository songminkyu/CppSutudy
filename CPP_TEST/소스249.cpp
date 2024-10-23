#include <iostream>
#include <type_traits>
#include <functional>

struct MyBind1 {
    int operator()(int a, int b) const { return a + b; }
};

struct MyBind2 {
    int operator()(int a, int b) const { return a + b; }
};

int f(int n1, int n2) { return n1 + n2; }

namespace std {
    template<>
    struct is_bind_expression<MyBind1> : public true_type {};
}

int main() {
    using namespace std::placeholders;
    std::bind(f, bind(MyBind1(), _1, _2), 2)(10, 11);   // OK
    std::bind(f, MyBind1(), 2)(10, 11);   // OK

    int r = std::bind(f, bind(MyBind2(), _1, _2), 2)(10, 11);   // OK
    std::cout << r << std::endl;
 //   std::bind(f, MyBind2(),               2)(10,11);   // ERROR
}