#include <iostream>
#include <random>
#include <array>
using namespace std;

/*
로그 정규 분포는 정규 분포에 지수 값을 취해 가장 빈번히 발생하는 빈도가 왼쪽 편으로 치우친 형태로 
어떤 사건의 확률이 크게 증가 했다가 급격히 낮아진다. 예를 들어 주식 시뮬레이션에서 수익을 정규 
분포형태로 증가시키기 위해서 수익률을 로그 정규 분포를 따르는 난수 값을 얻을 수 있을 수 있고, 경영 
시뮬레이션 게임에서 사원들에게 지급할 급여의 인상분의 결정에 난수를 포함한다고 했을 때 로그 정규 
분포를 사용할 수 있겠다.
*/
int main()
{
	//normal_distribution 템플릿 클래스 사용의 예

	std::default_random_engine eng;

	std::lognormal_distribution<double> dist(5.0, 2.0);

	array<int, 10> tmp = { 0, };

	for (int i = 0; i < 10000; ++i) {

		double number = dist(eng);

		if ((number >= 0.0) && (number < 10.0)) ++tmp[int(number)];

	}

	for (const auto& nd : tmp)
		std::cout << nd << std::endl;
}