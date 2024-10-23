#include <iostream>
#include <type_traits>

#include <vector>
#include <variant>

void test1(int) { std::cout << "test1\n"; }
void test2(int, int) { std::cout << "test2\n"; }
void test3(int, int, int) { std::cout << "test2\n"; }


int main() {
	using FNS = std::variant<void(*)(int), void(*)(int, int), void(*)(int, int, int)>;
	std::vector<FNS> fns;
	fns.push_back(test1);
	fns.push_back(test2);
	fns.push_back(test3);


	for (struct {
		void operator()(void(*f)(int)) { f(10); }
		void operator()(void(*f)(int, int)) { f(10, 20); }
		void operator()(void(*f)(int, int, int)) { f(10, 20, 30); }
	} action;
		auto fn : fns) {

		std::visit(action,
			fn
		);
	}

}