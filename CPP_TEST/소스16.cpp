
#include <iostream>

int main() {
	int datas[1][2][3] = {
		{{1,2,3},{4,5,6}}
	};

	for (auto& l1 : datas)
	{
		for (auto& l2 : l1)
		{
			for (auto& l3 : l2)
			{
				std::cout << l3 << std::endl;
			}
		}
	}
}