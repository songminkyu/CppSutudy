#include <iostream>
#include <fstream>
#include <vector>

decltype(auto) operator>>(std::ifstream& fp, std::vector<char>& data)
{
	do {
		if (!fp) break;
		auto size = fp.seekg(0, std::ios::end).tellg();
		fp.seekg(0, std::ios::beg);
		data.resize(size);
		fp.read(data.data(), data.size());
	} while (false);
	return (fp);
}

int main()
{
	std::ifstream fp(R"(d:\123123123.txt)");
	std::vector<char> data;
	fp >> data;
	for (auto&& datum : data)
	{
		std::cout << datum;
	}
}