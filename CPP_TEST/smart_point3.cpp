#include <iostream>
#include <memory>

int main()
{
	std::shared_ptr<int> a{ new int{10} };
	std::shared_ptr<int> other = a;

	/*
	shared_from_this 속성이 enable 하는 의미를 알아보자.
	위 코딩에서 
	a가 owner 한 메모리 주소를 p라고 부르면
	a에서 또다른 shared_ptr other를 만들수 있다(복사 생성자와 관점이 아닌...)
	이것을 "p에 대해 shared_from_this 속성이 enable" 하다고 말한다.

	기본적으로 shared_ptr, weak_ptr 는 shared_from_this 속성이 enable 하다.
	사용자 정의 형 타입에 대해서는 enable_shared_from_this 템플릿 클래스의 특수화로 this
	에 대해 shred_from_this 속성이 enable 하게 정의 할수 있다.
	
	*/
}