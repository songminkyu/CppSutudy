#include <iostream>

template< class ...ARGS>
auto print(const char* format, ARGS&&...args)->std::ostream& (*)(std::ostream&)
{
	return [&] {
		printf(format, args...);
	}(),
	[](std::ostream& cs)->decltype(auto) {
		return cs;
	};
}

int main()
{
	std::cout << print("%s ", "hello world") << " minkyu!!";
}