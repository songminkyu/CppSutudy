#include <iostream>
#include <random>
#include <array>
/*
비결정적 난수 생성기(Non-deterministic Random Generator)

일반적으로 난수 생성기는 시드 값을 기반으로 난수 수열을 생성한다. 시드 값은 반드시 결정적으로 입력해야 하는 값이다. 
seed라는 맴버에 인자로 값을 전달하기 때문이다. 표준 난수 라이브러리는 비결정적 난수 생성기 템플릿 클래스인 random_device를 제공해 준다.
random_device로 만들어 내는 난수는 시드 값이 필요 없는 난수여야 하므로 시스템적인 값이나 운영체제 혹은 하드웨어 리소스를 사용한다.

*/
int main() {
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(0, 99);
	std::cout << dist(mt) << std::endl;

	/************************************************/

	//random_device 값은 균등 분포를 보인다
	std::random_device randomDevice;
	std::array<int, 10> test = { 0, };
	std::uniform_int_distribution<int> _dist(0, 9);
	for (int n = 0; n < 1000000; ++n) {
		++test[_dist(randomDevice)];	
	}

	for (const auto& arr : test)
	{
		std::cout << arr << std::endl;
	}
}