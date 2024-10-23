#include <iostream>
#include <type_traits>

template <typename T>
void test(T&&) requires std::is_member_function_pointer_v<T> { std::cout << "Member function\n"; }

template <typename T>
void test(T&&) requires std::is_function_v<std::remove_cvref_t<T>> { std::cout << "Function\n"; }

void function_1() {}
class test_class
{
public:
    void function_2() {}
};

int main()
{
    test(&test_class::function_2);
    test(function_1);
}