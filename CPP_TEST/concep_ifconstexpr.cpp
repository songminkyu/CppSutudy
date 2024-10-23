#include <vector>
#include <list>
#include <array>
#include <cassert>

// afunction that returns the amount of space allocated in a container

auto allocated_size(const auto& container)
{
	if constexpr (requires{container.capacity(); }) 
	{
		return container.capacity();
	}
	else
	{
		container.size();
	}
}

int main()
{
	std::vector<int> vec;
	assert(allocated_size(vec) == 0);

	vec.push_back(1);
	assert(allocated_size(vec) == 1);

	vec.push_back(2);
	assert(allocated_size(vec) == 2);

	vec.push_back(3);
	assert(allocated_size(vec) == 4);

	std::array<int, 10> arryas;
	assert(allocated_size(arryas) == 10);

}