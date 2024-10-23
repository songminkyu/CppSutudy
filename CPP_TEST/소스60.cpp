#include <iostream>
#include <vector>
#include <type_traits>
//#include <concepts>

int f1(int) { std::cout << "#1\n"; return 0; }
int f4(int) { std::cout << "#2\n"; return 0; }
char f4(char) { std::cout << "#3\n"; return 'c'; }

template<typename T, auto N>
void call(T(* const (&fns)[N])(T)) {
	for (auto&& fn : fns) fn(1);
}

int main() {
	call({ &f1, &f4 });
}

