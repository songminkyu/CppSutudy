#include <iostream>
#include <random>
#include <array>
using namespace std;

/*


템플릿 클래스 생성자의 첫 번째 인자가 성공 횟수 k에 해당하고 두 번째 인자가 성공 확률 p를 의미한다.
음이항분포를 통한 난수 값은 결국 실패할 횟수가 된다.

*/

void main()
{
	//negative_binomial_distribution 클래스의 사용

	array<int, 20> tmp = { 0, };

	random_device seed;

	default_random_engine eng(seed());

	negative_binomial_distribution<> dist(2, 0.4);

	for (int i = 0; i < 100000; ++i) {

		int t = dist(eng);

		if (t > 19) continue;

		++tmp[t];

	}

	for (int i : tmp) { cout << i << " "; }
}