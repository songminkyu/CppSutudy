#include <iostream>
#include <mutex>
#include <chrono>
#include "stop_token.hpp"
#include "jthread.hpp"
int main()
{
	/*
	
	std::jthread 조금 더 일반적인 코딩 스타일
	프로그래머 제어권에 stop_source를 두는 것이 더 일반적인 경우.

	*/
	{
		using namespace std::literals;
		std::stop_source src{};
		std::stop_token p = src.get_token();

		std::jthread t(
			[&p]() {
				while (!p.stop_requested())
				{
					std::this_thread::sleep_for(1s);
					std::cout << "ehco\n";
				}
				std::cout << "endding\n";
			});
		std::this_thread::sleep_for(5s);
		src.request_stop();
	}

	return 0;
}