#include <iostream>
#include <type_traits>


/*

질문
1.두번째는 false아닌가요?
move assinable이 delete인데..
2.첫번째 예제도 copy assinable이 무비 assignable을
겸하는건 알겠는데 이게 그냥 초심자로서 외우기만 해서리..-,-;;
특별한 이유라도 있나요?
이렇게 두가지 기능을 수용한 이유가....

응답
move semantic 의미부터 일단 정확하게 정립할 필요가 있습니다.
이동된 객체는 최종적으로 왼쪽 피연산자에 상태가 옮겨집니다. 
하지만 오른쪽 피연산자는 객체 자체는 정상적이지만 객체의 상태는 특정할 수 없습니다. 
따라서 재사용하려면 observation 멤버 함수로 상태 검사함으로써 객체의 상태를 특정하고, 
이후에 적절히 사용해야 합니다.
따라서 copy semantics과 연산 결과가 유사하고 객체의 상태를 특정할 수 있습니다. 
결국 move 연산이 delete되지 않는 이상 copy semantics으로 대체될 수 있습니다.

std::is_assignable<T&, T&&>::value가 바로 is_move_assignable를 인데 주어진 
T에 &를 추가한 타입이 왼쪽에, &&를 추가한 타입이 오른쪽에 오는 연산을 허용한다는 의미이죠.
만약 T가 A라면 A& = A&& 연산이니 흔히 말하는 move 연산이지요. 하지만 T 자체가 A&라면 
A&+&는 A&로, A&&+&는 A&로 축약되면 A&=A& 즉, 유사 copy operator로 작동합니다.

*/


struct A {
    A& operator=(const A&) { return *this; }
    ~A() {}
};

struct D {
    D& operator=(D&&) = delete;
    D& operator=(const D&) = default;
    ~D() {}
};

int main() {
    std::cout
        << std::boolalpha
        << std::is_move_assignable_v<A> << std::endl;


    std::cout
        << std::boolalpha
        << std::is_move_assignable_v<D&> << std::endl;
}