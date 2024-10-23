#include <tuple> // std::apply
#include <iostream> // for demo only


/*
������ �Ϳ��� C ++ Ʈ�� : Ʃ���� �ݺ��ϱ����� �� ���� ����

*/
void iterate_tuple(auto f, auto tuple) {
    std::apply([&](auto... args) {
        ((void)f(args), ...);
        }, tuple);
}
int main() {
    auto tup = std::make_tuple(42, "hello", 3.14);
    iterate_tuple([](auto arg) {
        std::cout << arg << std::endl;
        }, tup);
}