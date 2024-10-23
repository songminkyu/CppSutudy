/*
transform_view�� range�� �Լ� ��ü�� �޾Ƽ� range ��ҷ� �Լ��� ȣ���� ��ȯ�� ������ ���ο� range view�� ������ݴϴ�.
���� partial transform view�� �۵��ϵ��� �ΰ��� �Լ� ȣ�� ��� �Լ��� ���������ν� �ΰ� �ݺ��� ������ �����ϰ� �۵��մϴ�.
*/

#include <iostream>
#include <vector>
#include <ranges>

int main() {
	using namespace std::ranges;
	auto three_modulo_string = [](auto p) {
		return std::vector<std::string>{"zero", "one", "two"}[p % 3];
	};

	std::vector<int> v{ 0,1,2,3,4,5 };

	for (auto&& item : views::transform(v, three_modulo_string)) {
		std::cout << item << " ";
	}
	std::cout << "\n";

	for (auto&& item : v
		| views::transform(three_modulo_string)) {
		std::cout << item << " ";
	}
}