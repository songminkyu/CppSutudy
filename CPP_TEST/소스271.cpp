#include <iostream>
#include <vector>
#include <ranges>

/*
ranges::filter_view는 input range과 predicator를 받아서 적절히 주어진 range를 predicator 조건이 만족하는 요소만을 range view합니다.
인자로 range를 받는 경우는 | 연산자를 통해 앞에 있는 요소를 range과 predicator를 분리하는 구문으로 작동하도록 함수 호출 템플릿 멤버 함수가 partial filter view를 만들어줍니다.
결국 두개의 반복 구문은 동일하게 작동합니다.
*/
int main() {
	using namespace std::ranges;

	auto even = [](auto p) { return (0 == p % 2); };
	std::vector<int> v{ 0,1,2,3,4,5 };

	for (auto&& item : views::filter(views::all(v), even)) {
		std::cout << item << " ";
	}
	std::cout << "\n";

	for (auto&& item : views::all(v) | views::filter(even)) {
		std::cout << item << " ";
	}
}
