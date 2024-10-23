#include <neo/iterator_concepts.hpp>
#include <neo/concepts.hpp>
#include <neo/test_concept.hpp>

#include <iostream>

int main()
{
    using namespace neo;    
    
    std::cout << default_initializable<int> << std::endl;
}