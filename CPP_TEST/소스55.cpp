#include <iostream>
#include <type_traits>

template<class T1, class T2>
concept is_same = std::is_same_v<T1, T2>;

template< typename ... Ts> requires (is_same<Ts, int>&&...)
void test(Ts... ts)
{
	[...args = ts] (){		
		(std::cout << ... << args);
		
	}();
}

int main()
{
	test(10, 20, 30);
}