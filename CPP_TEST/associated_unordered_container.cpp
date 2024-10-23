#include <iostream>
#include <string>
#include <map>
#include <unordered_map>

int main()
{
	std::map<std::string, int> datas1;
	datas1["test1"] = 10;

	if (datas1.contains("test1"))
	{
		std::cout << "found:test1" << std::endl;
	}

	std::unordered_map<std::string, int> datas2;
	if (!datas2.contains("test2"))
	{
		std::cout << "not found:test2" << std::endl;
	}
}