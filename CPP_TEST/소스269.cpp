#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <ranges>
#include <algorithm>

/*
stream�� iteratorȭ ���ִ� iterator adaptor�� �����ϴٸ�
stream�� range viewȭ���ִ� istream_view adaptor�� �����մϴ�.
istream_view �Լ��� ���ؼ� basic_istream_view ��ü�� ���� �� �ֽ��ϴ�.
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
