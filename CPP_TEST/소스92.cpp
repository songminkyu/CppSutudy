#include <iostream>
#include <random>
#include <string>
#include <iterator>
#include <algorithm>


std::ostream& operator <<(std::ostream& cs, const std::vector<std::string>& datas)
{
	for (auto&& item : datas)
	{
		cs << item << " ";
	}

	return cs;
}


int main()
{
	std::vector<std::string>
		in = { "1","2","3","4","5","6","7","8","9","10" }, out;

	std::sample(in.begin(), in.end(), std::back_inserter(out),
		5, std::mt19937{ std::random_device{}() });

	std::cout << "five random letters out of " << in << " : " << out << "\n";
}