#include <iostream>

#include "Four_Rule_Calc_wrapper.h"

int main()
{    
    Four_Rule_Calc_wrapper yahoo;
    double r = yahoo.sum(1, 2, "sum");
    std::cout << r << std::endl;
    
    r = yahoo.subtract(10, 2, "subtract");
    std::cout << r << std::endl;

    r = yahoo.division(5, 10, "division");
    std::cout << r << std::endl;

    r = yahoo.multiply(5, 5, "multiply");
    std::cout << r << std::endl;

    char text[10] = { 0, };    
    std::cin >> text;


}