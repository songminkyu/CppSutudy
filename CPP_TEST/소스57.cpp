#include <iostream>

template<class T>
struct Base {
	// Injected-class-name 은 type-name 또는 template-name 이다.
	Base* p;
};

template< class T>
struct Derived : public Base<T>
{
	// Injected-class-name 은 type-name 또는 template-name 이다.
	typename Derived::Base* p;
};

template <
	class T,
	template<class> class U = T::template Base>

/*
T::template Base는 Derived의 injected-class-name(type-name)일 경우에
Base 의 injected-class-name(template-name)을 지정 한다.
*/
struct Third{
	Third() = default;
};


int main()
{
	Third< Derived< int > > t{};
}
