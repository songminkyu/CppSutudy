#include <iostream>
#include <random>
#include <array>
using namespace std;

/*


0번부터 9번까지의 지역이 구역으로 나뉘어 일렬로 펼쳐져 있다고 가정하자. 
이때 0번 지역에서 70%의 확률로 잘 자라는 녹색의 잔디가 있고, 9번 지역으로 
갈수록 붉은색의 오염된 토양이 나와 잔디가 잘 안자란다고 가정하자. 0번부터 
9번까지 각 구역의 녹색의 비율을 난수로 설정하고 싶다면 어떻게 구현할 수 있을까.



geometric_distribution 클래스 사용의 예
*/

void main()
{
	array<int, 14> tmp = { 0, };

	random_device seed;

	default_random_engine eng(seed());

	geometric_distribution<int> dist(0.7);

	for (int i = 0; i < 100000; ++i) {

		++tmp[dist(eng)];

	}

	for (int i : tmp) { cout << i << " "; }
}