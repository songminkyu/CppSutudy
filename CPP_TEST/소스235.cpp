#include <iostream>
#include <vector>
#include <map>
#include <string>

template<typename Collection, typename ValueType>
bool contains(Collection&& collection, ValueType&& value)
{
    return std::find(
        std::cbegin(collection),
        std::cend(collection),
        std::forward<ValueType>(value))
        != std::cend(collection);
}

int main()
{		
    std::vector<std::string> s_v{"one","two","three","forth","five"};

	std::cout << std::boolalpha << contains(s_v, "asd");
    std::cout << "\n";
    std::cout << std::boolalpha << contains(s_v, "five");
}