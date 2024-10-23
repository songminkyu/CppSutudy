#include <iostream>
#include <random>
#include <functional>

using namespace std;

std::uniform_int_distribution<int>::result_type foo() {

	static std::default_random_engine engine{};

	static std::uniform_int_distribution<int> dist{ 1, 100 };

	return dist(engine);

}

int foo_bind_type() {

	default_random_engine engine;

	uniform_int_distribution<int> distribution(1, 1000);

	auto generator = std::bind(distribution, engine);

	int value = generator();

	return value;
}

void foo_engine_with_binding() {

	using TYPE = std::uniform_int_distribution<int>;

	TYPE dist;

	TYPE::result_type min = dist.min();

	TYPE::result_type max = dist.max();

	TYPE::param_type param = dist.param();

	dist.reset();

}

int main() {

	std::cout << foo() << std::endl;

	std::cout << foo() << std::endl;

	std::cout << foo() << std::endl;
	
	std::cout << foo_bind_type() << std::endl;
	std::cout << foo_bind_type() << std::endl;
	std::cout << foo_bind_type() << std::endl;
}