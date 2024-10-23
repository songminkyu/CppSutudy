#include <iostream>
#include <tuple>
/*
두번째 스샷이 약간 편법스럽지만 explicit object parameter 멤버 함수과 거의 동일하게 작동하는 코딩일 것이다. 
원리는 T&&로 바꿈으로서 perfect forward 구문이 작동하고 lvalue과 rvalue 의미를 그대로 살려주면, 
decltype(auto)에서 이를 감지해내는 방법이다. (바로 이전 샘플은 모두 rvalue로 인식하지만)
*/
#include <iostream>
#include <tuple>

namespace NS {
	class MyRect {
		int x{}, y{}, width{}, height{};
	public:
		MyRect(int x, int y, int width, int height) :x{ x }, y{ y }, width{ width }, height{ height }
		{}

		void print() const {
			std::cout << x << ' ' << y << ' ' << width << ' ' << height <<  '\n';
		}

		template<std::size_t IDX, typename T>
		friend decltype(auto) get(T&& rect) {
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
	struct tuple_size<NS::MyRect> : tuple_size<tuple<int, int, int, int>> {
	};

	template<std::size_t IDX>
	struct tuple_element<IDX, NS::MyRect> :tuple_element<IDX, tuple<int, int, int, int>> {
	};
}

int main() {
	do {
		NS::MyRect rect{ 0,10,1920,1080 };
		auto [x, y, width, height] = rect;
	} while (false);

	do {
		NS::MyRect rect{ 0,10,1920,1080 };
		auto& [x, y, width, height] = rect;
		y = 200;
		rect.print();
	} while (false);

	do {
		NS::MyRect const rect{ 0,10,1920,1080 };
		auto [x, y, width, height] = rect;
	} while (false);

	do {
		auto [x, y, width, height] = NS::MyRect{ 0,10,1920,1080 };
	} while (false);
}