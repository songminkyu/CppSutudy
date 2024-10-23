#include <iostream>
#include <string>
#include <vector>
#include <iterator>

int main()
{
	std::vector<std::string> datas = { "start","end" };

	auto inserter_iter = std::insert_iterator(datas, std::next(datas.begin()));

	for (int i = 0; i < 20; ++i)
	{
		*inserter_iter = "number : " + std::to_string(i);
	}
	
	for (auto&& item : datas) { std::cout << item << std::endl; }
}
