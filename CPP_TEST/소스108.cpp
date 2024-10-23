#include "cppitertools/zip_longest.hpp"
#include <boost/optional/optional_io.hpp>
#include <iostream>

int main()
{
    std::vector<int> ns1 = { 1, 2, 3 };
    std::vector<int> ns2 = { 10, 11, 12 };
    for (auto&& [a, b] : iter::zip_longest(ns1, ns2)) 
    {        
       std::cout << a << " , " << b << std::endl;
    }  
}