#include <iostream>
#include <random>
#include <string>
#include <iterator>
#include <algorithm>
#include <vector>

//·£´ýÀ¸·Î 2°³ »ùÇÃ »Ì±â.

int main()
{
	std::vector<std::string> names{
		"C++", "python","js","java","Switf","C#"
	};

	std::sample(
		names.begin(), names.end(),
		std::ostream_iterator<std::string>(std::cout, "\n"),
		2,
		std::mt19937{ std::random_device{}() }
	);
}