#include <iostream>
#include <variant>
#include <string>
#include <utility>

using R1 = std::variant<int, std::string>;
using R2 = std::variant<float, double>;
using RF = std::pair<R1, R2>;

struct F {
    
    //RF operator()(auto a, auto b) { return std::make_pair(a, b); } 16.8 버전에 지원 예정
    RF operator()(int a, float b) { return std::make_pair(a, b); }
    RF operator()(std::string a, double b) { return std::make_pair(a, b); }
    RF operator()(std::string a, float b) { return std::make_pair(a, b); }
};

int main() {
    R1 d1{ "hello" };
    R2 d2{ 10.4f };
    std::visit(
        F{},
        d1, d2);

    d1 = 1; d2 = 4.0;
    std::visit(
        F{},
        d1, d2);

    return 0;
}