#include <iostream>
#include <vector>

int main()
{
	auto fn = []<typename T>(std::vector<T> datas) {
		for (auto&& item : datas) std::cout << item << " ";
	};

	std::vector datas = { 1.1,1.2,1.3 };
	fn(datas);

}