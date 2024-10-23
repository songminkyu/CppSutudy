#include <iostream>
#include <concepts>
#include <vector>
template< typename T, typename...Ts>
struct first_type
{
	using type = T;
};

template<typename ... Args>
using first_type_t = typename first_type<Args...>::type;

template< typename T, typename...Ts>
inline constexpr bool are_same_v = std::conjunction_v<std::is_same<T, Ts>...>;

template< typename T, typename...Args>
concept same_as_first_type =
std::is_same_v<std::remove_cvref_t<T>,
    std::remove_cvref_t<first_type_t<Args...>>>;


template<typename...Args>
requires requires(Args...args)
{
	(... + args);
	requires are_same_v<Args...>;
	requires sizeof...(Args) > 1;
	{
		(... + args)
	}
	noexcept ->same_as_first_type<Args...>;
}
auto add(Args&&... args)
{
	return (... + args);
}

template<typename... Args>
concept TestAdd =
requires(Args... args)  
{
   	add(args...); 
};


int main()
{	
	std::cout << TestAdd<int> << std::endl;

	std::cout << add(1, 2, 3) << std::endl;

}