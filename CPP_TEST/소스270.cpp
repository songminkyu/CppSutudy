#include <iostream>
#include <vector>
#include <ranges>

/*
std::ranges::all �ν��Ͻ��� �Լ� ȣ�� ���ø� ��� �Լ��� ���� Ŭ������ ���޵� �ƱԸ�Ʈ�� ���� ����� 
�߻����� �ʵ��� �������� ������ range view�� ������ݴϴ�.
*/
int main() {
	using namespace std::ranges;

	std::vector<int> v{ 0,1,2,3,4,5 };
	for (auto&& item : views::all(v) | views::take(2)) {
		std::cout << item << " ";
	}
}
