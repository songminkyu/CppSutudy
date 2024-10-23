#include <iostream>
#include <charconv>
#include <system_error>
#include <string_view>
#include <array>

int main()
{
	std::array<char, 10> str;
	const int base = 36;
	if (auto [p, ec] = std::to_chars(str.data(), str.data() + str.size(), 12335, base);
		ec == std::errc())
		std::cout << std::string_view(str.data(), p - str.data());
	// 12335를 36진수로 표현한다면!
}