#include <iostream>

template<class Fun, class...Args>
auto repeat_imple(Fun&& fun, Args&& ...args)
{
	fun(std::forward<Args>(args)...);
	return [fun]<class...As>(As&&...as) { return repeat_imple(fun, std::forward<As>(as)...); };
}

template<class Fun>
auto repeat(Fun&& fun)
{
	return [fun]<class...As>(As&&...as) { return repeat_imple(fun, std::forward<As>(as)...); };
}

void test(int a, int b) { std::cout << a << ", " << b << std::endl; }

int main()
{
	repeat(test)(1, 2)(3, 4)(5, 6)(7, 8)(9, 10)(11, 12);
}