#include <iostream>


void fun(double(&&)[]) {
	std::cout << "#1 \n";
}
void fun(double (&&)[3]) {
	std::cout << "#2 \n";
}

int main() {
	fun({ 1.1 });
	fun({ 1.1, 2.2 });
	fun({ 1.1, 2.2, 3.3 });	
	fun({ 1.1, 2.2, 3.3, 4.4 });
}