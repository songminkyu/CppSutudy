#include <iostream>
#include <string>

template<class... Args>
auto strcat(Args...args)
{
	const auto total = (... + args.size());
	static std::string s;
	(s += ... += args);
	return s;
}

int main()
{
	std::string ls = "song";
	std::string rs = "min";
	std::string s = strcat(ls, rs);

	std::cout << s << std::endl;
}