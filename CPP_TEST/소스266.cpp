#include <iostream>
#include <vector>
#include <ranges>

/*
std::ranges::empty가 마치 함수처럼 보이지만, 실제로는 변수.
함수 객체 역할을 할뿐!!
std::ranges::empty_view<int>는 빈 요소를 가진 range view를 만들어준다.
std::ranges::views::empty는 템플릿 변수로 empty_view를 생성한다

*/
void empty_check(std::ranges::input_range auto& r) {
	using namespace std::ranges;
	std::cout << "empty:" << empty(r) << "\n";
}

int main() {
	std::vector v{ 1,2,3 };
	empty_check(v);
	v.clear();
	empty_check(v);

	std::ranges::empty_view<int> empty_range{};
	empty_check(empty_range); 

	empty_check(std::ranges::views::empty<int>);
}

