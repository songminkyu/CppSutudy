#include <iostream>
#include <sstream>
#include <thread>
#include <vector>
#include <chrono>
#include <latch>

#include "jthread.hpp"

int main() {
    using namespace std;

    std::cout << "이 일을 하기 위해서 5명이 필요합니다.\n";
    latch start_latch{ 1 };
    vector<jthread> workers;
    for (int i = 0; i < 5; ++i) {
        workers.emplace_back(
            [&, i]() {
                stringstream ready;
                ready << "멤버:" << i << "\n";
                std::cout << ready.str();
                start_latch.wait();

                stringstream cmt;
                cmt << "작업:" << i << "\n";
                std::cout << cmt.str();
            }
        );
    }
    std::this_thread::sleep_for(4s);
    std::cout << "일을 시작해볼까요?.\n";
    start_latch.count_down();
}