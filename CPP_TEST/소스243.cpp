/*
�Ʒ� ������ ���� �о��ֽø� ���ƿ�~
constraint�� ���� �� ������ conjunction�� disjunction�� �����Ѵ�.
�� ǥ������ �� ������ �� �����ڸ� ��������  ����ȭ�� ǥ�������� ����
�� ��, �� ǥ������ ��� ������ subexpression�� ��� �����ϰ� ���¿���
������ empty�ε�, �ٸ� ������ ���������� ���� ���� �� Ưȭ�� expression
���� ������ �� �ְ� �ȴ�.�� �����ڸ� �����ϸ� ���� �ٸ� �� ǥ������ ��
�� �� �ִٴ� ����  �ٽ��̴�.��̷ο� ������ �� ���� ������ !�� constraint 
�����ڰ� �ƴ� atomic constraint�� �ϳ��� ����ϰ� �ִٴ� ���̴�. �� �κ���
���� �����ұ� ����̱� �ѵ�, ���� ���� �Լ��� �ٸ� ���ƿ� �����ϸ� ���� �ٸ�
���� �Լ��� �з��ǵ�, atomic constraint�� �׷��ϴ�. ���� ǥ�����̶� �ٸ� 
���ƻ� �����ϸ�, ���� ǥ������ �ƴϴ�. ��, �� �Ұ��� �� ����� ���̴�.
������ ���� ������ atomic constraint���� �߿��ϸ� ������ ǥ�������� �Ǵ��Ѵ�.
���� atomic constraint�� ���� ��ü�� ������ �ؼ��Ǿ�� �ϰ�, �ؼ� �������� 
������ �߻��ϸ� requirement �Ҹ����� �ƴ϶� ���� ������ �и��ȴ�.
�׷��� �̷��� ������ ���ʷ� �Ʒ� ������ ����.
*/
#include <iostream>

template<class T> concept sad = false;

template<class T> void f1(T) requires(!sad<T>) { std::cout << "#1\n"; }
template<class T> void f1(T) requires(!sad<T>) && true { std::cout << "#2\n"; }

template<class T> concept not_sad = !sad<T>;
template<class T> void f2(T) requires not_sad<T>{std::cout << "#3" << "\n"; }
template<class T> void f2(T) requires not_sad<T> && true 
{std::cout << "#4" << "\n"; }

template <class T> concept sad_nested_type = sad<typename T::type>;
template <class T> void f3(T) requires (!sad<typename T::type>) {std::cout << "#5\n";}
template <class T> void f4(T) requires (!sad_nested_type<T>) {
	std::cout << "#2\n";
}

int main()
{
	// f1(42); Error ambiguous
	f2(42); //#4
	// f3(42); // ���� ����
	f4(42); //#2
}