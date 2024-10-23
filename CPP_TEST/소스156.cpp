#include <iostream>
using namespace std;

#if false
template< class T>
void func(T* t) {

	if constexpr (std::is_class_v<T>) { cout << "T is user-defined type\n"; }
	else { cout << "T is primitive type\n"; }
}
#else
template<class T, typename = std::enable_if_t<std::is_class_v<T>>>
void func(T* t) {
	cout << "T is user-defined type\n";
}

template<class T, std::enable_if_t<std::is_integral_v<T>, T> = 0>
void func(T* t) { // NOTE: function signature is NOT-MODIFIED
	cout << "T is primitive type\n";
}

#endif

int primitive_t = 6;
struct { char var = '4'; }class_t;
struct struct_t {};

template<typename T>
class is_class_type {
	template<typename C> static char test(int C::*);
	template<typename C> static double test(...);
public:
	enum { value = sizeof(is_class_type<T>::test<T>(0)) == sizeof(char) };
};


int _tmain()
{
	func(&class_t);
	func(&primitive_t);

	std::cout << is_class_type<struct_t>::value << std::endl;
	std::cout << is_class_type<int>::value << std::endl;
}