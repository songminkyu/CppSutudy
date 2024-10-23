#include <iostream>
#include <random>
#include <array>
using namespace std;

/*
베르누이 분포의 사용

베르누이 분포는 bernoulli_distribution 클래스를 사용하며 고정된 
특정 확률로 참 이나 거짓을 판단할 때 사용한다. 동전 던지기처럼 앞/뒤, 성공/실패, 
켜짐/꺼짐의 난수를 구할 수 있는 것이다. 예를들어 게임 내부에서 다른 가상의 캐릭터에게 전화를 건다면
해당 가상 캐릭터가 남자인지에 대한 인자로 0.5를 인자로 넣은 베르누이 분포를 사용할 수 있으며 주사위를 던졌을 때 
6이 나오는가에 대한 인자로 분포 생성자에 1 / 6을 확률값으로 넣은 베르누이 분포를 사용할 수 있을 것이다.



30%의 확률로 true 혹은 false의 랜덤값을 구할 수 있다.
*/

void main()
{
	array<int, 2> tmp = { 0, };

	random_device seed;

	default_random_engine eng(seed());

	bernoulli_distribution dist(0.3);

	bool result = dist(eng);

	for (int i = 0; i < 100000; ++i) {

		if (dist(eng)) { ++tmp[1]; }

		else { ++tmp[0]; }

	}

	for (int i : tmp) { cout << i << " "; }
}