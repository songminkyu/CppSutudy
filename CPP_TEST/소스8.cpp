#include <iostream>
#include <tuple>

const char* test(char, char) { return "hellow world \n"; }
auto& test2(int) { std::cout << "called\n"; return test; }

template<class OUTR, class... OUTR_ARGS, class ...INTER_ARGS>
auto call(OUTR(&
(&fn)(INTER_ARGS...)
)(OUTR_ARGS...))
{
	return [=](INTER_ARGS&& ... args1, OUTR_ARGS&& ...args2) {
		return(fn(args1...))(args2...);
	};
}

int main()
{
	std::cout << call(test2)(1, 'c', 'd');
}