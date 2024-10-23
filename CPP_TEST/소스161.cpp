#include <iostream>

typedef const int IA[3];
void h1(IA& data) {
	for (auto&& datum : data)
	{
		std::cout << datum << std::endl;
	}
}

typedef const int(&RIA)[3];
void h2(RIA& data) {
	for (auto&& datum : data)
	{
		std::cout << datum << std::endl;
	}
}

int main()
{
	h1({ 1,2,3 });
	h2({ 1,2,3 });
}