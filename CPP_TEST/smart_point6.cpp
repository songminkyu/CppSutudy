#include <iostream>
#include <memory>

/*
shared_ptr를 이용해서

ownership과 저장된 포인터를 다르게 가져가는 예제.
*/

struct B {
    virtual void test() {}
    ~B() { std::cout << "~B\n"; }
};

struct A {
    struct :B {
        void test() override { std::cout << ":\n"; }
    } datas{};

    ~A() { std::cout << "~A\n"; }

    void log() { std::cout << "A::log\n"; }
    operator B* () { return &datas; }
};


int main() {
    std::shared_ptr<A> a{ new A{} };
    std::shared_ptr<B> b{ a, *a };

    b->test();
    a->log();
}
