#include <iostream>
#include <vector>
#include <ranges>

/*
std::ranges::empty�� ��ġ �Լ�ó�� ��������, �����δ� ����.
�Լ� ��ü ������ �һ�!!
std::ranges::empty_view<int>�� �� ��Ҹ� ���� range view�� ������ش�.
std::ranges::views::empty�� ���ø� ������ empty_view�� �����Ѵ�

*/
void empty_check(std::ranges::input_range auto& r) {
	using namespace std::ranges;
	std::cout << "empty:" << empty(r) << "\n";
}

int main() {
	std::vector v{ 1,2,3 };
	empty_check(v);
	v.clear();
	empty_check(v);

	std::ranges::empty_view<int> empty_range{};
	empty_check(empty_range); 

	empty_check(std::ranges::views::empty<int>);
}

