#include <iostream>
#include <array>
#include <algorithm>

template<typename A, size_t N, typename T>
void Fill(A(&array)[N], const T& val) {
	std::fill((T*)array, (T*)(array + N), val);
}

int main()
{
	std::array<std::array<int, 3>, 3> arr = { {{5, 8, 2}, {8, 3, 1}, {5, 3, 9}} };
	
	for (auto ar : arr)
	{		
		for (auto a : ar)
		{		
			std::cout << a;
		}
		std::cout << "\n";
	}


	constexpr int xy = 4;
	const int xxxx = 100;
	using Cell = std::array<unsigned char, 8>;

	std::array<Cell, xy* xy> board;	

	board.fill({ {0x30, 0x31, 0x31, 0x32, 0x31, 0x80, 0, 0} });
	
	std::for_each(board.cbegin(), board.cend(), [xy, O = 1](const auto& c) mutable
	{
		std::cout << c.data() << ((O++ % xy) ? "" : "\n");
	});

	int c3[10][20][30];
	Fill(c3, 100);	
	std::cout << c3[2][3][1] << std::endl;

}