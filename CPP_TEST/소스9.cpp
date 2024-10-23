#include <iostream>
#include <type_traits>

void test(char,char){
	std::cout << "hellow world" << std::endl;
}
auto test2(int) { return test; }
auto test3(float) { return test2; }

int main() {
	void(&fn1)(char, char) = test;
	void(*(&fn2)(int))(char, char) = test2;
	void(*(*(&fn3)(float))(int))(char, char) = test3;

	fn1(
		'1', '1'
	);

}