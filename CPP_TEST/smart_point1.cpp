#include <iostream>
#include <memory>

struct A {
    ~A() {}
};

namespace std {
    template<>
    struct default_delete<::A> {
        void operator()(A* a) {
            std::cout << "my deleter" << std::endl;
            delete a;
        }
    };

    template<>
    struct default_delete<::A[]> {
        void operator()(A* a) {
            std::cout << "my deleter[]" << std::endl;
            delete[] a;
        }
    };
}

int main()
{
    std::unique_ptr<A>    ptr1{ new A{} };
    std::unique_ptr<A[]>  ptr2{ new A[10] };
}