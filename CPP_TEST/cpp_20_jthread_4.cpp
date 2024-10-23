#include <iostream>
#include <mutex>
#include <chrono>
#include "jthread.hpp"

int main()
{
	using namespace std::chrono_literals;

	std::jthread t{[](std::stop_token st) {

		puts("start");
		int i = 0;
		while (!st.stop_requested())
		{			
			std::cout << i++ << std::endl;			
			//do work
		}
		puts("stop");

	}};
	
	for (int i = 0; i < 50; ++i)
	{						
		std::this_thread::yield();		
		std::this_thread::sleep_for(100ms);
	}
	
}