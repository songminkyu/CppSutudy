
#include <iostream>

template< class T, auto M, auto N> void m(T const(&)[M][N])
{
	std::cout << M << ',' << N;
}

int main() {
	
	m({
		{1,2,3},
		{4,5,6},
		});

	
}