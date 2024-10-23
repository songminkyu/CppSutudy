#include <iostream>
#include <mutex>
#include <chrono>
#include "jthread.hpp"

int main() {
    {
        using namespace std::literals;
        std::jthread t(
            [](std::stop_token p) {
                while (!p.stop_requested()) {
                    std::this_thread::sleep_for(1s);
                    std::cout << "echo\n";
                }
                std::cout << "ending\n";
            });
        std::this_thread::sleep_for(5s);
    }
    
    return 0;
}