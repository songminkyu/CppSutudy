#include <iostream>
#include <iterator>
#include <string>
#include <vector>


/*
std::indirectly_comparable

In the <iterator> header you¡¯ll not only find concepts related to callables but more generic ones as well. 
Such as whether two types are inderictly comparable. That sounds interesting, let¡¯s take a simple example:

*/
template <typename Il, typename Ir, typename F>
void foo(Il leftIterator, Ir rightIterator, F function) requires std::indirectly_comparable<Il, Ir, F> {
    std::cout << std::boolalpha << function(*leftIterator, *rightIterator) << '\n';
}

int main()
{
    using namespace std::string_literals;

    auto binaryLambda = [](int i, int j) { return 42; };
    auto binaryLambda2 = [](int i, std::string j) {return 666; };

    std::vector ints{ 15, 42, 66 };
    std::vector floats{ 15.1, 42.3, 66.6 };
    foo(ints.begin(), floats.begin(), binaryLambda);
    //   foo(ints.begin(), floats.begin(), binaryLambda2); // error: use of function 'void foo(Il, Ir, F) requires  indirectly_comparable<Il, Ir, F, std::identity, std::identity> 
}


/*

In this case, I¡¯ve been left a bit puzzled by the documentation:

* As a third template parameter it has class R which normally would refer to ranges.
* But then according to its definition, it calls std::indirect_binary_predicate with R forwarded in the first position.
* In std::indirect_binary_predicate, in the first position, you accept a class F and F stands for a callable (often a function). 

Why isn¡¯t R called F? Why binary predicates are not mentioned in the textual description?

Probably only because this is still the beginning of the concepts journey. I¡¯m actually going to submit a change request on this item.

*/