#include <iostream>
#include <sstream>
#include <thread>
#include <vector>
#include <chrono>
#include <barrier>
#include "jthread.hpp"

/*
C++20에 추가된 std::barrier 사용해보기_msvc 2019
std::barrier는 재사용 가능한 std::latch라고 할 수 있겠죠.
*/
int main() {
    using namespace std;

    barrier start_barrier{ 5 };
    vector<jthread> workers;
    std::cout << "5 member started.\n";
    for (int i = 0; i < 5; ++i) {
        workers.emplace_back(
            [&, i]() {
                {
                    std::this_thread::sleep_for(1s);
                    stringstream stage;
                    stage << "STAGE 1:" << i << "\n";
                    std::cout << stage.str();
                    start_barrier.arrive_and_wait();
                }
                if (0 == i) {
                    start_barrier.arrive_and_drop();
                    std::cout << "4 member left\n";
                    return;
                }

                {
                    std::this_thread::sleep_for(1s);
                    stringstream stage;
                    stage << "STAGE 2:" << i << "\n";
                    std::cout << stage.str();
                    start_barrier.arrive_and_wait();
                }
                if (1 == i) {
                    start_barrier.arrive_and_drop();
                    std::cout << "3 member left\n";
                    return;
                }

                {
                    std::this_thread::sleep_for(1s);
                    stringstream stage;
                    stage << "STAGE 3:" << i << "\n";
                    std::cout << stage.str();
                    start_barrier.arrive_and_wait();
                }

                if (2 == i) {
                    start_barrier.arrive_and_drop();
                    std::cout << "2 member left\n";
                    return;
                }
                {
                    std::this_thread::sleep_for(1s);
                    stringstream stage;
                    stage << "STAGE 4:" << i << "\n";
                    std::cout << stage.str();
                    start_barrier.arrive_and_wait();
                }
            }
        );
    }
    std::this_thread::sleep_for(5s);
}