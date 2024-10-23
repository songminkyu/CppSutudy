#include <iostream>
#include "DelegateDemo.h"
#include "ArticleSamples.h"
#include "Benchmark.h"

using namespace std;

int main() {

	ArticleSampleSet().Demo();
	DelegateSample::Demo();
	std::cout << std::endl << "=== Benchmarks: ===" << std::endl << std::endl;
	Benchmark::Run();

	return 0;

} /* main */
