#include <iostream>
#include <tuple>
/*
사용자 정의 "Structured binding declaration" 구문을 스펙 문서를 보고 구현하다보면, explicit object parameter 멤버 함수가 얼마나 
유용한지 새삼 느끼게 된다.
그나마 앞서 일부를 구현한 msvc에서도 컴파일 내부 오류를 만들어 내지만, cv-qualifier, ref-qualifier를 한방에 싹 밀어버릴 수 있는 
구문은 friend get 함수과 template<typename T>를 활용하면 어느 정도 깔끔하게 구현할  수 있지만, 
뭐니뭐니해도 this auto&&구문보다는 조잡스럽다.
friend 단어를 제거하고 , MyRect&& 부분을 this auto&&로 전환하면 C++23의 explicit object parameter 멤버 함수가 만들어진다.
MyRect&&이 perfect forward 구문으로 역할을 할 수 없기 때문에, lvalue에 대해서는 에러를 발생한다. explicit object parameter 
멤버 함수는 이마저도 해결할듯?? 아직 테스트되지 않음. 설계 목적 중 하나가 ref-qualifier를 포워딩하는 것이니.
*/

namespace NS {
	class MyRect {
		int x{}, y{}, width{}, height{};
	public:
		MyRect(int x, int y, int width, int height) :x{ x }, y{ y }, width{ width }, height{ height }
		{}

		template<std::size_t IDX>
		friend decltype(auto) get(MyRect&& rect) {
			if constexpr (IDX == 0) {
				return (rect.x);
			}
			else if constexpr (IDX == 1) {
				return (rect.y);
			}
			else if constexpr (IDX == 2) {
				return (rect.width);
			}
			else {
				return (rect.height);
			}
		}
	};
}

namespace std {
	template<>
	struct tuple_size<NS::MyRect>: tuple_size<tuple<int, int, int, int>> {
	};

	template<std::size_t IDX>
	struct tuple_element<IDX, NS::MyRect>:tuple_element<IDX, tuple<int,int, int, int>>{
	};
}

int main() {
	do {
		NS::MyRect rect{ 0,10,1920,1080 };
		auto [x, y, width, height] = rect;
	} while (false);

	do {
		NS::MyRect const rect{ 0,10,1920,1080 };
		auto [x, y, width, height] = rect;
	} while (false);

	do {
		auto [x, y, width, height] = NS::MyRect{ 0,10,1920,1080 };
	} while (false);
}