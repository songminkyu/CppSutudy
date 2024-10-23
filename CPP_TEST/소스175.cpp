#include <iostream>

template<typename T> concept C = requires (T t) { t.f(); };
template<typename T> concept D = C<T> && requires (T t) { t.f(); };

template<typename T> class S { };
template<C T>        class S<T> { public: void print() { std::cout << "#A\n"; } };
template<D T>        class S<T> { public: void print() { std::cout << "#B\n"; } };

struct A {
    void f() {};
};

template<typename T>
struct B {
    void f() {};
};

int main() {
    S<A> s1{};
    s1.print();        
}
