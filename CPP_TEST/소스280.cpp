#include <iostream>
#include <chrono>

int main()
{
	//C++20���� �߰��� �Ǿ� �ִ� �������� ���� ũ�γ� ���̺귯���� �Ϸ���� ����.

	using namespace std::literals;
	using namespace std::chrono;

	auto t1 = Sunday;
	auto t2 = Saturday;

	for (; t1 != t2 += days{ 1 }) {
		std::cout << t1.c_encoding() << '\n';
	}
}
