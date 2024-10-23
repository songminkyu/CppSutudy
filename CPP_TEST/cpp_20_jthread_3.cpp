#include <iostream>
#include <sstream>
#include <chrono>
#include <jthread.hpp>

/*
    https://wandbox.org/permlink/01m2qklaJ21TPGM3 (std::thread 버전)
    https://wandbox.org/permlink/LLq4OxGPNPyICrDE (std::jthread 버전)

    std::jthread의 조금 더 일반화된 버전은 ActiveObject(쓰레드를 내부 품고 있는 심장이 있는 클래스) 형태겠죠. 
    아래처럼. 당연히 std::thread과 연계해도 문제없음. 어떤 형태든지 상상하기 나름!!
    stop_source에 stop 신호를 보내면 atomic하게 stop_requested()를 읽어낼 수 있음(stop 상태를 공유하는 구조, 
    promise-future 설계 구조와 유사).즉 하나로 여러개의 쓰레드를 문제없이 제어 가능. 
    10개 쓰레드를 운영하면서 동시에 종료 시그널을 날려주는 구조~

*/
//표준 thread로 구현

class Actor_thread {
public:

	[[nodiscard]]
	std::stop_source run(std::uint64_t cnt) {
		std::stop_source src{};
		std::stop_token p = src.get_token();

		using namespace std::literals;
		while (cnt-- > 0) {
			std::thread(
				[p]() {
					while (!p.stop_requested())
					{
						std::this_thread::sleep_for(500ms);
						std::stringstream ss;
						ss << "echo:\t" << std::this_thread::get_id() << '\n'; //해당 쓰레드 아이디를 가져옴
						std::cout << ss.str(); //echo 및 쓰레드 아이디 출력
					}
					std::stringstream ss;
					ss << "endding:\t" << std::this_thread::get_id() << '\n';
					std::cout << ss.str();
				}
			).detach();
		}
		return src;
	}
};

class Actor_jthread {
	std::vector<std::jthread> ths;
public:	
	void run(std::uint64_t cnt) {
		using namespace std::literals;

		while (cnt-- > 0){
			ths.emplace_back(
				[](std::stop_token p) {
					while (!p.stop_requested()){
						std::this_thread::sleep_for(500ms);
						std::stringstream ss;
						ss << "echo : \t" << std::this_thread::get_id() << '\n';
						std::cout << ss.str();
					}
					std::stringstream ss;
					ss << "ending :\t" << std::this_thread::get_id() << '\n';
					std::cout << ss.str();
				}
			);
		}
	}
};

int actor_thread_test()
{
	{
		Actor_thread actor{};
		auto ender = actor.run(10);
		std::cin.get();
		ender.request_stop();
	}
	std::cin.get();
	return 0;
}

int actor_jthread_test()
{
	{
		Actor_jthread actor{};
		actor.run(10);
		std::cin.get();		
	}
	std::cin.get();
	return 0;
}
int main()
{

/*
   true  : actor_thread_test
   false : actor_jthread_test
*/
	
#if false
	actor_thread_test();
#else
	actor_jthread_test();
#endif
}