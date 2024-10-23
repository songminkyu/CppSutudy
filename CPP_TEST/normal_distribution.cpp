#include <iostream>
#include <random>
#include <array>
using namespace std;

/*
normal_distribution 템플릿 클래스는 RealType의 타입의 난수를 생성한다. 
값들의 평균 발생 확률은 평균이 mean에 부여한 값이 되고 분산이 S*S인 정규 분포를 따른다.
*/
int main()
{
	//normal_distribution 템플릿 클래스 사용의 예

	std::default_random_engine eng;

	std::normal_distribution<double> dist(5.0, 2.0);

	array<int, 10> tmp = { 0, };

	for (int i = 0; i < 10000; ++i) {

		double number = dist(eng);

		if ((number >= 0.0) && (number < 10.0)) ++tmp[int(number)];

	}

	for (const auto& nd : tmp)
		std::cout << nd << std::endl;
}