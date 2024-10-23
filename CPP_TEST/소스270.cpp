#include <iostream>
#include <vector>
#include <ranges>

/*
std::ranges::all 인스턴스는 함수 호출 템플릿 멤버 함수를 가진 클래스로 전달된 아규먼트를 성능 비용이 
발생하지 않도록 포워딩해 적절히 range view를 만들어줍니다.
*/
int main() {
	using namespace std::ranges;

	std::vector<int> v{ 0,1,2,3,4,5 };
	for (auto&& item : views::all(v) | views::take(2)) {
		std::cout << item << " ";
	}
}
