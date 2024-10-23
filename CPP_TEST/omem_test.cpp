#include <vector>
#include "../CPP_TEST/omem/omem.hpp"

template <class Al>
static void Benchmark(Al al)
{
	using T = std::allocator_traits<Al>;
	for (auto i = 0; i < 10000000; ++i)
		T::deallocate(al, T::allocate(al, 1), 1);
}


int main(int argc, char* argv[])
{
	Benchmark(omem::Allocator<double>{});
}
