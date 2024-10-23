#include <iostream>
#include <map>
#include <string>

int main()
{
	std::initializer_list<std::pair<const std::string, int>> inputs = {
		{"test1",1},{"test2",2}
	};

	std::map<std::string,int > datas{ inputs };

	for (auto&& [key, mapped] : datas)
	{
		std::cout << key << " : " << mapped << std::endl;
	}
}