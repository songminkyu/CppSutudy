/*
transform_view는 range과 함수 객체를 받아서 range 요소로 함수를 호출해 반환된 값으로 새로운 range view를 만들어줍니다.
역시 partial transform view가 작동하도록 두개의 함수 호출 멤버 함수를 제공함으로써 두개 반복문 구문이 동일하게 작동합니다.
*/

#include <iostream>
#include <vector>
#include <ranges>

int main() {
	using namespace std::ranges;
	auto three_modulo_string = [](auto p) {
		return std::vector<std::string>{"zero", "one", "two"}[p % 3];
	};

	std::vector<int> v{ 0,1,2,3,4,5 };

	for (auto&& item : views::transform(v, three_modulo_string)) {
		std::cout << item << " ";
	}
	std::cout << "\n";

	for (auto&& item : v
		| views::transform(three_modulo_string)) {
		std::cout << item << " ";
	}
}