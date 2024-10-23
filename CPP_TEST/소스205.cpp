#include <string_view> // only for use in the example
#include <iostream>

template <class... Lambdas>
struct overloads : Lambdas... {
    using Lambdas::operator()...;
};
template <class... Lambdas>
overloads(Lambdas...)->overloads<Lambdas...>;
int test() {
    auto foo = overloads{
      [](int) { return 42; },
      [](double) { return 73; },
      [](std::string_view) { return 314; }
    };
    return foo("hello") + foo(1) + foo(3.14);
}

int main()
{
    std::cout << test() << std::endl;
}