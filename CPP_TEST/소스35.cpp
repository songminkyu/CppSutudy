#include <iostream>

int main() {
	alignas(char) alignas(double) char buffer[sizeof(double)];
	std::cout << reinterpret_cast<int>(buffer) % alignof(double);

	/*
	char 묶음의 메모리에 실제로 double 타입이 실제적으로 사용한다면 : 
	char의 정렬 규약과 double 정렬 규악을 모두 준수 하도록 메모리의 시작 위치를 조정하기
	*/
}