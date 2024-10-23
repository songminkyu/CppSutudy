#include <iostream>
#include <random>
#include <array>
#include <map>

using namespace std;

/*
gamma_distribution은 모수인 알파와 베타를 생성자로 받으며 이를 조회할 수 있는 alpha()와 beta() 맴버 함수를 제공해 주고 있다. 
gamma_distribution은 0보다 큰 난수를 생성하며 템플릿 인자로 결과 값에 대한 타입을 받는다.
*/
void test(const double a, const double b) {

	std::mt19937 gen(1701);

	std::gamma_distribution<> distr(a, b);

	std::cout << std::endl;

	std::cout << "min() == " << distr.min() << std::endl;

	std::cout << "max() == " << distr.max() << std::endl;

	std::cout << "alpha() == " << distr.alpha() << std::endl;

	std::cout << "beta() == " << distr.beta() << std::endl;

	std::map<double, int> histogram;

	for (int i = 0; i < 10; ++i) {

		++histogram[distr(gen)];

	}

	int counter = 0;

	for (const auto& elem : histogram) {

		std::cout << ++counter << ": " << elem.first << std::endl;

	}

	std::cout << std::endl;

}

void test2()
{

	/*
	알파값과 베타값이 각각 2.0인 각 구간에서의 빈도를 구하기 위해 충분한 만큼의 난수를 발생시켜 
	그래프를 구하면 gamma_distribution가 감마 분포를 보인다는 것을 알 수 있다.

	gamma_distribution의 빈도를 구하는 코드의 예
	*/
	std::default_random_engine eng;

	std::gamma_distribution<double> dist(2.0, 2.0);

	array<int, 10> tmp = { 0, };

	for (int i = 0; i < 10000; ++i) {

		double number = dist(eng);

		if (number < 10) ++tmp[int(number)];

	}

	for (int t : tmp) {

		std::cout << t << std::endl;

	}
}

int main()
{
	test(0.2, 4.9);
	test2();
}