#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <concepts>

class thread_group {
	std::vector<std::thread> members;
public:
	template<std::invocable FN>
	thread_group(std::uint64_t n, FN&& f)
	{
		for(int i = 0; i < n; ++i)
			members.emplace_back(f);
	}

	~thread_group() {
		for (auto& item : members) {
			if (item.joinable())
				item.join();
		}
	}

};

int main()
{
	thread_group fg(10, []() {std::cout << "hellow world\n"; });
}