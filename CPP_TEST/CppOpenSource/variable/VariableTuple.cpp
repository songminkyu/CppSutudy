#include <iostream>
#include <tuple>

/*
여러 타입으로 다항식 타입을 만들고, 다시 타입 분해하고, 반환 타입을 얻어내고, 타입적으로 하는 작업이 의미가 있습니다. 
원래 유사 코딩이 2개 더 있었는데, 일단 코딩량이 작은 습작 코딩입니다. 반환 타입이 void일 때, 반환 타입 추적이 실패하고, 
함수의 파라미터 타입이 명시적 타입으로 추출하지 않아, 조금만 변형해도, 전체 코딩이 에러 상태가 됩니다.
*/

int add(short, int)      { std::cout << "#1\n"; return 10; }
float subtract(int, int) { std::cout << "#2\n"; return 0.0f; }

auto test(auto&&... fs) {
	return [...fs = fs](auto&&... args) {
		using R = std::tuple<decltype(fs(args...))...>;
		return R{ fs(args...)... };
	};
}


int main() {
     auto fs = test(add, subtract);
	 fs(10, 20);
}
