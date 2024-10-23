#include <iostream>

int main() {
	//MS에선 왜 안되지....?
	auto fn = new auto{
		[](int r) { std::cout << "hello world!!" << r;  }
	};

	(*fn)(10);

	delete fn;

}