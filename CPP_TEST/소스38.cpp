#include <iostream>
#include <string>

template<typename...Args>
auto strcat(Args...args) {
	const auto total = (... + args.size());
	std::string s;
	s.reserve(total);
	(s += ... += args);
	return s;

}

int main()
{
	using namespace std;
	std::cout << strcat("test1"sv, "test2"sv);
}