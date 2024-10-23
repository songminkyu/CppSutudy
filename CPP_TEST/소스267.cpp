#include <iostream>
#include <vector>
#include <ranges>

/*
std::ranges::single_view는 요소 하나만을 가진 range view를 만들어줍니다.
std::range::views::single는 함수 호출  템플릿 멤버를 가진 클래스의 인스턴스로 전달된 값을 single_view 객체의 아규먼트로 포워딩한 값을 반환합니다.
*/
template<std::ranges::sized_range R>
void size_check(R&& r) {
	using namespace std::ranges;
	std::cout << "size:" << size(r) << "\n";
}

int main() {
	std::vector v{ 1,2,3 };
	size_check(v);

	std::ranges::single_view m1{ 123 };
	size_check(m1);

	size_check(std::ranges::views::single(34));
}
