#include <iostream>
#include <tuple>

const char* test(char, char) { return "hellow world \n"; }
auto& test2(int) { return test; }

template<class OUTR, class... OUTR_ARGS, class ...INTER_ARGS>
OUTR call(OUTR(&
(&fn)(INTER_ARGS...)
)(OUTR_ARGS...),
std::tuple<INTER_ARGS...> args1, std::tuple< OUTR_ARGS...> args2)
{
	return std::apply(std::apply(fn, args1 ), args2);
}

int main()
{
	std::cout << call(test2, { 1 }, { 'c','d' });
}