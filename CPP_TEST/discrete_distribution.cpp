#include <iostream>
#include <random>
#include <array>
using namespace std;

/*
표본 분포 그룹에는 이산 분포(Discrete Distribution), 피스와이즈 상수 분포(Piecewise Constant Distribution)), 
피스와이즈 리니어 분포(Piecewise Linear Distribution)가 있다. 세 개의 분포는 유사하다.

이산 분포는 특정 분포에 대한 비율을 지정해 줄 수 있다. 이를 위해 discrete_distribution 
템플릿 클래스가 가지고 있는 여러 생성자중 initializer_list를 받는 생성자가 존재한다.

*/
int main()
{
	//discrete_distribution 클래스의 사용

	std::default_random_engine eng;
	
	std::discrete_distribution<int> dist = { 2, 2, 1, 1, 2, 2, 1, 1, 2, 2 };

	array<int, 10> tmp = { 0, };

	for (int i = 0; i < 100000; ++i) {

		int number = dist(eng);

		++tmp[number];

	}

	for (int t : tmp) {

		std::cout << t << std::endl;

	}
	/*
	충분히 많은 수의 난수를 생성하면 discrete_distribution 템플릿 
	클래스를 생성할 때 인자로 부여한 initializer_list의 비율 만큼 결과 값의 
	분포가 반영된 난수가 생성됨을 확인할 수 있다.
	*/
}