#include <iostream>
#include <memory>

struct A
{
	~A() {}
};

struct DELE_A {
	int count = 0;

	void operator()(A* a)
	{
		std::cout << "count : " << ++count << std::endl;
		delete a;
	}
};

int main()
{
	DELE_A dele{};
	std::unique_ptr<A, DELE_A&> ptr1{ new A{}, dele };
	std::unique_ptr<A, DELE_A&> ptr2{ new A{}, dele };
	std::unique_ptr<A, DELE_A&> ptr3{ new A{}, dele };
	std::unique_ptr<A, DELE_A&> ptr4{ new A{}, dele };
	ptr4 = std::move(ptr3);

	return 0;

}