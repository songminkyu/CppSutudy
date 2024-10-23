#include <iostream>
#include <ranges>

/*
ranges::iota_view는 초기값에서 증가하는 range view를 만들어줍니다.
ranges::views:iota 변수는 함수 호출 멤버 함수를 가진 클래스로 전달된 값을 ranges::iota_view의 아규먼트로 포워딩한 값을 반환합니다.
아직 msvc 배포판에는 미구현 상태지만, 깃허브에는 구현된 상태입니다. 조만간 배포되면 가능한 코딩입니다.
*/
int main() {
	using namespace std;
	for (auto&& item : ranges::views::iota(1, 10)) {
		std::cout << item << " ";
	}

	for (auto&& item : ranges::iota_view(10, 20)) {
		std::cout << item << " ";
	}
}
