#include <iostream>
#include <tuple>

/*

function... 어떻게 미분할 것인가? 어떻게 적분할 것인가? 프로그래밍 세상의 유사 수학~

*/

template <typename... Rs, typename ...Args>
auto marge_fn(Rs(*...fs)(Args)) {
	return[fs...](Args&&...args){
		using REST = std::tuple<Rs...>;
		return REST(fs(args)...);
	};
}

int t1(float) { return 10; }
float t2(char) { return 10.5f; }

int main() {
	auto rets = marge_fn(t1, t2)(10.5f, 'c' );
	std::cout << std::get<0>(rets) << std::endl;
	std::cout << std::get<1>(rets) << std::endl;
}