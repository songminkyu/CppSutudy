#include <barrier>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

/*
C++23 스펙에서 barrier의 completion function 호출 시점에 대한 미묘한 변경 사항이 존재합니다.
일단 C++20 기준 코딩.
기존 구현 컴파일러의 표준 라이브러리는 C++23에서 관련 구현을 조정할 예정입니다.
관련 변경 사항을 보니, arrive하는 마지막 thread에서 completion function 호출을 
요구하던 기존 방식에서 arrive_and_wait하는 thread가 존재하면, completion function 호출을 양보하는 구조입니다.
이에 따라 엔비디아 가속 장치에서는 조금 더 효율적인 방법으로 thread 스케쥴이 가능하지는군요.
또한 아래 예제처럼 arrive 호출과 arrive_and_wait 호출이 존재할 때, arrive 호출을 포함하는 
thread는 멈추지 않고 계속 다음 작업을 진행할 수 있게 되는.
*/
int main()
{
    const auto workers = { "Anil", "Busara", "Carl" };
 
    auto on_completion = []() noexcept
    {
        // locking not needed here
        static auto phase = "... done\n" "Cleaning up...\n";
        std::cout << phase;
        phase = "... done\n";
    };
 
    std::barrier sync_point(std::ssize(workers), on_completion);
 
    auto work = [&](std::string name)
    {
        std::string product = "  " + name + " worked\n";
        std::cout << product;  // ok, op<< call is atomic
        sync_point.arrive_and_wait();
 
        product = "  " + name + " cleaned\n";
        std::cout << product;
        sync_point.arrive_and_wait();
    };
 
    std::cout << "Starting...\n";
    std::vector<std::jthread> threads;
    threads.reserve(std::size(workers));
    for (auto const& worker : workers)
        threads.emplace_back(work, worker);
}
