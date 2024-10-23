// lambdaCaptureThis.cpp

#include <iostream>
#include <string>
/*
Implicitly Copy of the this Pointer
The following program captures implicitly the this pointer by copy.
*/
struct Lambda {
    auto foo() const {
        return [=] { std::cout << s << std::endl; };   // (1) 
    }
    std::string s = "lambda";
    ~Lambda() {
        std::cout << "Goodbye" << std::endl;
    }
};

auto makeLambda() {
    Lambda lambda;                                     // (2)                               
    return lambda.foo();
}                                                      // (3)


int main() {

    std::cout << std::endl;

    auto lam = makeLambda();
    lam();                                             // (4)                                                               

    std::cout << std::endl;

}