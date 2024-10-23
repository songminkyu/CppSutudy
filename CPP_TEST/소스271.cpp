#include <iostream>
#include <vector>
#include <ranges>

/*
ranges::filter_view�� input range�� predicator�� �޾Ƽ� ������ �־��� range�� predicator ������ �����ϴ� ��Ҹ��� range view�մϴ�.
���ڷ� range�� �޴� ���� | �����ڸ� ���� �տ� �ִ� ��Ҹ� range�� predicator�� �и��ϴ� �������� �۵��ϵ��� �Լ� ȣ�� ���ø� ��� �Լ��� partial filter view�� ������ݴϴ�.
�ᱹ �ΰ��� �ݺ� ������ �����ϰ� �۵��մϴ�.
*/
int main() {
	using namespace std::ranges;

	auto even = [](auto p) { return (0 == p % 2); };
	std::vector<int> v{ 0,1,2,3,4,5 };

	for (auto&& item : views::filter(views::all(v), even)) {
		std::cout << item << " ";
	}
	std::cout << "\n";

	for (auto&& item : views::all(v) | views::filter(even)) {
		std::cout << item << " ";
	}
}
