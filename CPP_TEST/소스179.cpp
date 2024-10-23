#include <iostream>
#include <concepts>

//매개변수 Auto 는 msvc 16.8 에 지원 예정 
std::integral auto sum(std::integral auto a, std::integral auto b) {
    return a + b;
}

int main() {
    std::integral auto  v = sum(1, 50);
    std::cout << v;
    return 0;
}