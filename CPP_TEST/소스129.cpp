
#include <cmath>
#include <iostream>
#include <memory>
#include <string>
#include <set>
/*
Stateless Lambdas can be default-constructed and copy-assigned
Lambdas can be used in unevaluated contexts
Admittedly, this is quite a long title. Maybe the term stateless lambda is new to you.
A stateless lambda is a lambda that captures nothing from its environment. Or to put it the other way around.
A stateless lambda is a lambda, where the initial brackets [] in the lambda definition are empty. For example,
the lambda expression auto add = [ ](int a, int b) { return a + b; }; is stateless.

When you combine the features, you get lambdas, which are quite handy.

Before I show you the example, I have to add a few remarks. std::set such as all other
ordered associative containers from the standard template library  (std::map, std::multiset,
and std::multimap) use per-default std::less to sort the keys. std::less guarantees that all
keys are ordered lexicographically in ascending order.
The declaration of std::set on cppreference.com shows you
*/

template <typename Cont>
void printContainer(const Cont& cont) {
    for (const auto& c : cont) std::cout << c << "  ";
    std::cout << "\n";
}

int main() {

    std::cout << std::endl;

    std::set<std::string> set1 = { "scott", "Bjarne", "Herb", "Dave", "michael" };
    printContainer(set1);

    using SetDecreasing = std::set < std::string, decltype([](const auto& l, const auto& r) { return l > r; }) > ;           // (1)
    SetDecreasing set2 = { "scott", "Bjarne", "Herb", "Dave", "michael" };
    printContainer(set2);     // (2)

    using SetLength = std::set < std::string, decltype([](const auto& l, const auto& r) { return l.size() < r.size(); }) > ; // (1)
    SetLength set3 = { "scott", "Bjarne", "Herb", "Dave", "michael" };
    printContainer(set3);     // (2)

    std::cout << std::endl;

    std::set<int> set4 = { -10, 5, 3, 100, 0, -25 };
    printContainer(set4);

    using setAbsolute = std::set<int, decltype([](const auto& l, const auto& r) { return  std::abs(l) < std::abs(r); }) > ; // (1)
    setAbsolute set5 = { -10, 5, 3, 100, 0, -25 };
    printContainer(set5);    // (2)

    std::cout << "\n\n";

}
