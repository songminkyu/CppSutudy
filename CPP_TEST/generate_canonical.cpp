#include <iostream>
#include <random>
#include <array>
using namespace std;


void main()
{
	//generate_canonical 클래스 사용의 예

	std::random_device rd;

	mt19937 mt(rd());

	for (int i = 0; i < 5; ++i) {
		cout << generate_canonical<double, numeric_limits<double>::digits>(mt) << " ";

	}
}