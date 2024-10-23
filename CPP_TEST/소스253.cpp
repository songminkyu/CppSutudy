#include <concepts>
#include <iostream>
#include <typeinfo> 


/*
std::totally_ordered for defined comparisons

std::totally_ordered helps to accept types that specify all the 6 comparison operators (==,!=,<,>,<=,>=) and that the results are consistent with a strict total order on T.

*/
struct NonComparable {
	int a;
};

struct Comparable {
	auto operator<=>(const Comparable& rhs) const = default;
	int a;
};


template <typename T>
void fun(T t) requires std::totally_ordered<T> {
	std::cout << typeid(t).name() << " can be ordered\n";
}

int main() {
	NonComparable nc{ 666 };
	//   fun(nc); // Not OK: error: use of function 'void fun(T) requires  totally_ordered<T> [with T = NonComparable]' with unsatisfied constraints
	Comparable c{ 42 };
	fun(c);
}


/*
In the above example, you can also observe how to easily use the <=> (a.k.a. spaceship) operator to generate all the comparison operators.

If you are looking for more information on the <=> operator, I highly recommend reading this article from Modernes C++.

*/