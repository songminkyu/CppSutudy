#include <vector>
#include <initializer_list>
#include <iostream>

/*
C++17���� �����ϱ� ������
class template deduction guide�� ���� Ʈ�� ���!!
�Ϲ������� Ŭ���� ���ø� �ƱԸ�Ʈ�� �߷��� �� �����ϴ�.
�ֳ��ϸ� �ƱԸ�Ʈ �߷��� �Լ����� ���Ǵ� overload resolution 
�������� ����Ǵµ� Ŭ������ �Լ��� �ƴϴϱ��.
������ ǥ�ؿ����� class template deduction guide��� �Լ��� ���� ���̵带 
�����ؼ� Ŭ�������� ���� �߷������� ������ �Լ��� �������� overload resolution�� 
����� �߷��ϵ��� ���̵��� �ְ�, �߷е� ����� Ŭ���� ���ø� �߷� ����� ����ϴ� �����Դϴ�.
*/
template <class T, class U, class V>
struct Foo {
	T bar;
	std::vector<U> baz;
	V foobar;
};
template <class T, class U, class V>
Foo(T, std::initializer_list<U>, V)->Foo<T, U, V>;
int main() {
	auto test = Foo{ 42, {3.14, 2.718, 1.618}, 'x' };


	std::cout << test.bar << std::endl;	
	std::cout << test.foobar << std::endl;

}