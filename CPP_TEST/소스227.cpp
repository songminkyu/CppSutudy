#include <iostream>
#include <type_traits>

// underlying_type를 기반으로 분기하기


template <typename Enumeration>
auto as_integer(Enumeration const value)
-> typename std::underlying_type<Enumeration>::type
{
	return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}


template< class T1, class T2>
concept underlying_fixed = std::is_same_v<std::underlying_type_t<T1>, T2>;

void test(underlying_fixed<int> auto& v)
{
	
	std::cout << "#1" << std::endl;
}

void test(underlying_fixed<unsigned int> auto v)
{
	std::cout << "#2" << std::endl;
}

enum class A1 : int {
	RED,
	GREEN,
	BLUE

};

enum class A2 : unsigned int {
	RED,
	GREEN,
	BLUE
};

int main()
{
	A1 a1{};
	A2 a2{};

	test(a1);
    test(a2);

	std::cout << as_integer(A1::GREEN) << std::endl;

}