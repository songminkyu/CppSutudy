#include <iostream>
#include <sstream>
#include <thread>
#include <vector>
#include <chrono>
#include <barrier>
#include "jthread.hpp"

int main() {
    using namespace std;

    barrier start_barrier{ 5 };
    vector<jthread> workers;
    for (int i = 0; i < 5; ++i) {
        workers.emplace_back(
            [&, i]() {
                {
                    std::this_thread::sleep_for(1s);
                    stringstream stage;
                    stage << "STAGE 1:" << i << "\n";
                    std::cout << stage.str();
                }
                start_barrier.arrive_and_wait();

                {
                    std::this_thread::sleep_for(1s);
                    stringstream stage;
                    stage << "STAGE 2:" << i << "\n";
                    std::cout << stage.str();
                }
                start_barrier.arrive_and_wait();

                {
                    std::this_thread::sleep_for(1s);
                    stringstream stage;
                    stage << "STAGE 3:" << i << "\n";
                    std::cout << stage.str();
                }
                start_barrier.arrive_and_wait();
            }
        );
    }
    std::this_thread::sleep_for(5s);
}