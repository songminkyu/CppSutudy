#include <iostream>
#include <optional>

void schrodinger()
{
	std::optional<bool> alive = false;

	//false를 주면 2개의 조건문이 실행
	//true를 주면 첫번째 조건문이 실행
	// 신기하네...

	if (alive) {
		std::cout << "is a alive" << std::endl;
	}

	if (alive == false) {
		std::cout << "is a dead" << std::endl;
	}

}

int main()
{
	schrodinger();
}