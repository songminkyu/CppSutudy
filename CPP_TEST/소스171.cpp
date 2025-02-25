#include <type_traits>
#include <iostream>

// 역시 리눅스는 되는데,,, msvc는 안되는군....

template<typename T>
concept Integral = std::is_integral<T>::value;

void overload(Integral auto t) {
    std::cout << "auto : " << t << std::endl;
}

void overload(Integral auto t) {
    std::cout << "Integral : " << t << std::endl;
}

void overload(long t) {
    std::cout << "long : " << t << std::endl;
}

int main() {

    std::cout << std::endl;

    overload(3.14);             // (1)
    overload(2010);             // (2)
    overload(2020l);            // (3)

    std::cout << std::endl;

}