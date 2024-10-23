#include <iostream>
#include <random>
#include <array>
using namespace std;
/*
균일 분포

균일 분포는 엔진으로부터 얻는 임의의 값을 균일한 분포로 재배치해 준다. 
일반적으로 rand() 함수 결과 값을 %를 이용해 범주를 지정하여 사용한 부분에 균일 분포를 사용할 수 있다. 
난수 생성기를 통한 난수 값이 범주 사이의 값이 되도록 uniform_int_distribution 클래스의 템플릿 인자에 필요한 최대, 
최소 값을 지정한다. 만일 자료형이 실수 타입이라면 uniform_real_distribution 클래스를 사용할 수 있다.



임의의 엔진에 연결된 균일 분포 클래스 사용과 결과의 예

CustomEngine 클래스는 내부적으로 설정된 최소값부터 최대값까지 값을 순서대로 반환한다. 결국 CustomEngine은 
완전하게 균등 분포 값을 반환하기 때문에 분포 클래스의 결과값을 쉽게 확인할 수 있다. uniform_int_distribution의 
템플릿 클래스의 범주를 0에서 9까지 설정하고 CustomEngine을 연결시킨 후 
충분히 큰 횟수만큼 난수를 생성하면 결과 값들이 균일 분포를 이루는 것을 확인할 수 있다.
*/
class CustomEngine {

public:

	typedef unsigned int result_type;

	static result_type min() { return 0; }

	static result_type max() { return 100000000; }

	explicit CustomEngine() : cache_(0) { }

	result_type operator()() { return ++cache_; }

private:

	unsigned int cache_;

};

int main()

{

	array<int, 10> tmp = { 0, };

	CustomEngine ce;

	uniform_int_distribution<> dis(0, 9);

	for (int i = 0; i < 100000; ++i) {

		++tmp[dis(ce)];

	}

	for (int i : tmp) {

		cout << i << " ";

	}

}

