
#include <iostream>

/*
C++20에서 람다가 unevaluated-context에 허용이 되면서 이러한 코딩이 가능해졌어요~. 
아직 적용된 컴파일러는 gcc뿐이지만..(그 동안 스펙 문서에서 된다고해서 주기적으로 검사해온 보람이~)

deleter나 comparator를 그냥 람다로 긁어주세요~ 카드 긁어주듯~

https://godbolt.org/z/xpyUqk
*/

#include <iostream>
#include <memory>
struct A {
};

using MY_PTR = std::unique_ptr <
	A,
	decltype([](auto p) { delete(p); std::cout << "called\n"; })
> ;

int main() {
	MY_PTR a{ new A };
}
