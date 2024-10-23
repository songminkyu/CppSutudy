#include <tuple>
#include <iostream>

int main()
{
	std::apply(
			[](auto &&...args)
			{
				((std::cout << std::forward<decltype(args)>(args) << ' '), ...);
			}, std::make_tuple(1, 3, 5, "test")		
		);
}