#include <iostream>
#include <memory>


/*
사용자 정의 클래스에 shared_from_this 속성 부여하기

(생각보다 멋있는 코딩이 되어버렸군. 마치 인터페이스 컨테이너 같은 느낌의 코딩)

*/
struct B {};
struct C {};

struct A : std::enable_shared_from_this<A> {
    A() = default;

    struct :B { } data_b{};
    struct :C { } data_c{};

    operator std::shared_ptr<A>() {
        std::cout << "called#1\n";
        return this->shared_from_this();
    }

    operator std::shared_ptr<B>() {
        std::cout << "called#2\n";
        return { this->shared_from_this(), &data_b };
    }
    operator std::shared_ptr<C>() {
        std::cout << "called#3\n";
        return { this->shared_from_this(), &data_c };
    }

    ~A() { std::cout << "~A\n"; }
};

int main() {
    std::shared_ptr<A> a{ new A{} };
    {
        std::shared_ptr<A> other1 = a;   // shared_ptr의 shared_from_this 속성을 사용함.
        std::shared_ptr<A> ohter_a = *a; // 사용자 정의한 shared_from_this 속성 사용.
        std::shared_ptr<B> other_b = *a;
        std::shared_ptr<C> other_c = *a;
    }
}