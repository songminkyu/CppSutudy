#include <iostream>
#include <sstream>
#include <thread>
#include <vector>
#include <chrono>
#include <latch>

#include "jthread.hpp"

int main() {
    using namespace std;

    std::cout << "�� ���� �ϱ� ���ؼ� 5���� �ʿ��մϴ�.\n";
    latch start_latch{ 1 };
    vector<jthread> workers;
    for (int i = 0; i < 5; ++i) {
        workers.emplace_back(
            [&, i]() {
                stringstream ready;
                ready << "���:" << i << "\n";
                std::cout << ready.str();
                start_latch.wait();

                stringstream cmt;
                cmt << "�۾�:" << i << "\n";
                std::cout << cmt.str();
            }
        );
    }
    std::this_thread::sleep_for(4s);
    std::cout << "���� �����غ����?.\n";
    start_latch.count_down();
}