#include <iostream>
#include <vector>
#include <ranges>

/*
std::ranges::single_view�� ��� �ϳ����� ���� range view�� ������ݴϴ�.
std::range::views::single�� �Լ� ȣ��  ���ø� ����� ���� Ŭ������ �ν��Ͻ��� ���޵� ���� single_view ��ü�� �ƱԸ�Ʈ�� �������� ���� ��ȯ�մϴ�.
*/
template<std::ranges::sized_range R>
void size_check(R&& r) {
	using namespace std::ranges;
	std::cout << "size:" << size(r) << "\n";
}

int main() {
	std::vector v{ 1,2,3 };
	size_check(v);

	std::ranges::single_view m1{ 123 };
	size_check(m1);

	size_check(std::ranges::views::single(34));
}
