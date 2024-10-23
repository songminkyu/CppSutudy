#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <ranges>
#include <algorithm>

/*
stream를 iterator화 해주는 iterator adaptor가 존재하다면
stream를 range view화해주는 istream_view adaptor가 존재합니다.
istream_view 함수를 통해서 basic_istream_view 객체를 만들 수 있습니다.
*/
int main() {
	using namespace std::ranges;

	auto words = std::istringstream{ "one two three" };
	for (auto&& item : istream_view<std::string>(words)) {
		std::cout << std::quoted(item) << " ";
	}
	std::cout << "\n";

	auto floats = std::istringstream{ "1.1 2.2 3.3" };
	copy(istream_view<float>(floats), std::ostream_iterator<float>{std::cout, " , "});
}
