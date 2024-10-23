#include <iostream>
#include <thread>
#include <atomic>

void run(const std::atomic_bool& passed)
{
	for(; !passed;)
	{
	}
	std::cout << "passed\n";
}

int main()
{
	std::atomic_bool passed = false;
	auto th = std::thread(run, std::ref(passed));
	std::string cmd;

	while (std::cin >> cmd)
	{
		if (cmd == "inc") passed = true;
		if (cmd == "exit") break;
	}

	th.join();
}