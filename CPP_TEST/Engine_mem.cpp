#include <iostream>
#include <random>
using namespace std;

/*
표준 C++ 난수 라이브러리

표준 난수 라이브러리를 이용하기 위해서는 #include <random>을 소스코드에 포함한다. 해당 라이브러리에는 그동안 C 형식의 
라이브러리에서 제공해 줬던 난수 라이브러리보다 더욱 다양하고 정밀한 난수 생성기를 제공해 준다. 표준 라이브러리의 난수생성기는 
기본적으로 균등 난수 생성기(uniform random number generator)이며 엔진(Engine)과 분포(Distribution)라는 두 개의 개념으로 분리하여 
구성되어 진다.

엔진은 균등 분포(Uniform Distribution)되는 최소값과 최대값 사이의 난수를 발생시킨다. 예를 들어 특정 엔진의 최소값과 최대값을 각각 
1과 10으로 설정했다면 이 엔진을 이용하여 1에서 10사이의 난수를 얻을 수 있다. 일반적인 난수생성기와 마찬가지로 엔진에 
시드 값을 설정할 수 있으며 시드 값은 임의의 또 다른 엔진으로 부터 얻는 난수를 사용할 수도 있다.

*/
void foo(unsigned int seed) {

	default_random_engine engine;

	engine.seed(seed);

	default_random_engine::result_type v = engine();

	default_random_engine::result_type min = engine.min();

	default_random_engine::result_type max = engine.max();

	default_random_engine::result_type defaultSeed

		= default_random_engine::default_seed;

	cout << "min : " << min << endl << "max : " << max << endl;

	cout << "value : " << v << endl;

	engine.seed();

	cout << "Default seed : " << defaultSeed << endl;

	cout << "value : " << engine() << endl;

	cout << "value : " << engine() << endl;

	engine.seed();

	cout << "value : " << engine() << endl;

}

int main()
{
	foo(12345);
}