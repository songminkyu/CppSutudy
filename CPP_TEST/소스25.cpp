#include <iostream>
#include <string>
#include <unordered_map>

int main()
{
	std::unordered_map<std::string, int> dics;
	dics["A"] = 32;
	dics["B"] = 43;

	for (auto&& [key, value] : dics)
	{
		std::cout << "key : " << key << " ,value : " << value << std::endl;
	}




}