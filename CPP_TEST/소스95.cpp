#include <iostream>

namespace NS {
    void test(int) { std::cout << "#1"; }
}

void test(int) { std::cout << "#2"; }

int main()
{
    test(10);
    if (void(&test)(int) = NS::test
        ; true) {
        test(10);
    }

    return 0;
}