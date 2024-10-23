#include <iostream>
#include <chrono>

int main()
{
	//C++20에는 추가는 되어 있는 상태지만 아직 크로노 라이브러리가 완료되지 않음.

	using namespace std::literals;
	using namespace std::chrono;

	auto t1 = Sunday;
	auto t2 = Saturday;

	for (; t1 != t2 += days{ 1 }) {
		std::cout << t1.c_encoding() << '\n';
	}
}
