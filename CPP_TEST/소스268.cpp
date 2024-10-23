#include <iostream>
#include <ranges>

/*
ranges::iota_view�� �ʱⰪ���� �����ϴ� range view�� ������ݴϴ�.
ranges::views:iota ������ �Լ� ȣ�� ��� �Լ��� ���� Ŭ������ ���޵� ���� ranges::iota_view�� �ƱԸ�Ʈ�� �������� ���� ��ȯ�մϴ�.
���� msvc �����ǿ��� �̱��� ��������, ����꿡�� ������ �����Դϴ�. ������ �����Ǹ� ������ �ڵ��Դϴ�.
*/
int main() {
	using namespace std;
	for (auto&& item : ranges::views::iota(1, 10)) {
		std::cout << item << " ";
	}

	for (auto&& item : ranges::iota_view(10, 20)) {
		std::cout << item << " ";
	}
}
