#include <iostream>
#include <ranges>
#include <string>
#include <vector>
#include <typeinfo> 


/*
Concepts in the <ranges> header

In the <ranges> header you¡¯ll find concepts describing requirements on different types of ranges.
Or simply that a parameter is a range. But you can assert for any kind of ranges, like input_range, output_range, forward_range, etc.

*/


template <typename R>
void foo(R range) requires std::ranges::borrowed_range<R> {
	std::cout << typeid(range).name() << " is a borrowed range\n";
}

int main()
{
	std::vector numbers{ 15, 43, 66 };
	std::string_view stringView{ "is this borrowed?" };
	//   foo(numbers); // error: use of function 'void foo(R) requires  borrowed_range<R> [with R = std::vector<int, std::allocator<int> >]' with unsatisfied constraints
	foo(stringView);
}


/*
The above example checks whether a type satisfies the concept of a borrowed_range. We can observe that a std::string_view does, while a vector doesn¡¯t.

If you are curious, having a borrowed range means that a function can take it by value and can return an iterator obtained from it without any dangers of dangling. For more details, click here.
*/