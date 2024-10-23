#include <iostream>
#include <tuple>
template<typename...T, typename... ARGS>
auto f(T(*...fns)(ARGS...)) {

	return [fns...](ARGS... args) -> std::tuple<T...> {
		return { fns(args...)... };
	};
}

int   add(int a, int b) { return a + b; }
float subtract(int a, int b) { return a * 10.19f + b; }
int   add10(int a, int b) { return a * 10 + b * 10; }

int main() {
	auto r = f(add, subtract, add10)(10, 20);
	std::cout << get<0>(r) << "\t" << get<1>(r) << "\t" << get<2>(r);
}