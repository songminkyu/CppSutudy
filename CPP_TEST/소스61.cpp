
#include <iostream>
/*
T(&)[N]으로의 template argument deduction에서 N의 배열의 길이로 추론되고, 
독립적으로 실행된 각 element로부터 동일한 T가 추론되어야 한다.

T(&)[10]으로의 template argument deduction에서는 배열 길이는 추론하지 않고 
독립적으로 실행된 각 element로부터  동일한 T가 추론되면 된다.
*/

template<class T> void j(T const(&datas)[4]) {

	for (auto&& item : datas) {
		std::cout << item << std::endl;
	}
}

int main() {
	j( { 1,2,0,0 } );
}