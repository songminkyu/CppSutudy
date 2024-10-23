#include <iostream>
#include <functional>

int plusFunction(int a, int b)
{
	return a + b;
}

auto plusLambda = [](int a, int b) {
    return a + b;
};

int main() {

    std::cout << std::endl;

    auto twoThousandPlus1 = std::bind_front(plusFunction, 2000);         // (1)
    std::cout << "twoThousandPlus1(20): " << twoThousandPlus1(20) << std::endl;

    auto twoThousandPlus2 = std::bind_front(plusLambda, 2000);           // (2)
    std::cout << "twoThousandPlus2(20): " << twoThousandPlus2(20) << std::endl;

    auto twoThousandPlus3 = std::bind_front(std::plus<int>(), 2000);     // (3)
    std::cout << "twoThousandPlus3(20): " << twoThousandPlus3(20) << std::endl;

    std::cout << "\n\n";

    using namespace std::placeholders;

    auto twoThousandPlus4 = std::bind(plusFunction, 2000, _1);           // (4)
    std::cout << "twoThousandPlus4(20): " << twoThousandPlus4(20) << std::endl;

    auto twoThousandPlus5 = [](int b) { return plusLambda(2000, b); };  // (5)
    std::cout << "twoThousandPlus5(20): " << twoThousandPlus5(20) << std::endl;

    std::cout << std::endl;

}