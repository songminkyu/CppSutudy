#include <iostream>
#include <concepts>

//�Ű����� Auto �� msvc 16.8 �� ���� ���� 
std::integral auto sum(std::integral auto a, std::integral auto b) {
    return a + b;
}

int main() {
    std::integral auto  v = sum(1, 50);
    std::cout << v;
    return 0;
}