#include <iostream>
#include <memory>


/*
shared_ptr 객체의 get()의 반환값이 nullptr되는 것과 use_count()의 반환값이 0이 되는 것을 별개!!
*/
struct A {
    ~A() { std::cout << "~A\n"; }
};


int main() {
    std::shared_ptr<A> a{ new A{} };
    std::shared_ptr<void> avoid{ a, nullptr };
    std::cout << "use_count:" << avoid.use_count() << std::endl;
    if (avoid) {
        std::cout << "avoid.get()!=nullptr\n";
    }
    else {
        std::cout << "avoid.get()==nullptr\n";
    }
}