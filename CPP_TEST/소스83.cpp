
#include <iostream>

template<class Inputit, class T>
constexpr Inputit find(Inputit first, Inputit last, const T& value)
{
	for (; first != last; ++first) {
		if (*first == value) {

			first = first + 1;

			return first;
		}
	}
	return last;
}


int main()
{
	
	const char* p = "123;123123";
	const char* s = "not find";

	char* n1 = find((char*)p, (char*)s, ';');

	std::cout << n1 << std::endl;
}