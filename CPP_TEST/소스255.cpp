#include <iostream>
#include <iterator>
#include <vector>

/*
Concepts in the <iterator> header

In the <iterator> header, you¡¯ll mostly find concepts that will come in handy when you deal with algorithms. It makes sense if 
you think about it, as the functions of the <algorithms> header operate on the containers through iterators, not directly on the containers.

std::indirect_unary_predicate<F, I>
There are concepts related to callables, e.g. you can specify that you accept only unary predicates. First, what is a predicate? A predicate is 
a callable that returns either a bool value or value that is convertible to a bool. A unary predicate is a predicate that takes one parameter as its input.
I know that the following example is not very realistic, it¡¯s only for demonstrational purposes.
*/

template <typename F, typename I>
void foo(F fun, I iterator) requires std::indirect_unary_predicate<F, I> {
    std::cout << std::boolalpha << fun(*iterator) << '\n';
}

int main()
{
    auto biggerThan42 = [](int i) {return i > 42; };
    std::vector numbers{ 15, 43, 66 };
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        foo(biggerThan42, it);
    }
}

/*
* 
In the above example foo takes a function and an iterator and the concept std::indirect_unary_predicate ensures that the passed-in function can take the value pointed by the iterator and return a bool instead.

*/