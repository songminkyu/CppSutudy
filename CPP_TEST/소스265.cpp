#include <iostream>
#include <iterator>
#include <numeric>

int main() {
	using namespace std;
	partial_sum(istream_iterator<double, char>(cin),
		istream_iterator<double, char>(),
		ostream_iterator<double, char>(cout, " "));
}
