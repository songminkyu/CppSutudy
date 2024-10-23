module;

#include "foo.h"

export module M;

template<typename T> int use_f()
{
	N::X x;
	return f(x, 123);

		
}

template<typename T> int use_g() {
	N::X x;
	return g((T(), x));

}

int k = use_h<int>();