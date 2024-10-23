#include <iostream>
#include <tuple>

template <typename Fp, typename... Args>
void func_execute(Fp&& fp, std::tuple<Args...>&& args) { std::apply(fp, args); }

template <typename Fp>
void func_execute(Fp&& fp) { fp(); }

template <typename Fp, typename... Args>
void test(Fp&& fp, Args&&... args)  requires (sizeof...(args) == 0)
{
    func_execute(fp);
}

template <typename Fp, typename... Args>
void test(Fp&& fp, Args&&... args)  requires (sizeof...(args) != 0)
{
    func_execute(fp, std::make_tuple(args...));
}

void test_1() { std::cout << "Hello World\n"; }
void test_2(int a) { std::cout << "Hello World : " << a << '\n'; }

int main()
{
    test(test_1);
    test(test_2, 3);
}