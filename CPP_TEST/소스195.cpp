#include <iostream>

class A {
public:
    void do_something(int x) const {
        std::cout << "Do something with " << x << std::endl;
    }
};

template <typename T, typename... Ints>
void do_many_things(const T& t, Ints... nums) {
    // 각각의 인자들에 대해 do_something 함수들을 호출한다.
    (t.do_something(nums), ...);
}
int main() {
    A a;
    do_many_things(a, 1, 3, 2, 4);
}