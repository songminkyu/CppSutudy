// ConsoleApplication2.cpp : �� ���Ͽ��� 'main' �Լ��� ���Ե˴ϴ�. �ű⼭ ���α׷� ������ ���۵ǰ� ����˴ϴ�.
//

#include <iostream>

//Clan������ �����ϴ� �ڵ�
/*
Cute C++ trick of the day: Use a non-type template parameter pack of an unlikely-to-collide type to guard
against users accidentally giving explicit template parameters. You can even mix this with required explicit
parameters! https://godbolt.org/z/MKazxn5on

(Credit: Abseil's MakeSpan)
*/
template <int&... ExplicitArgumentBarrier, class T>
void Foo(T arg) {
    // T is always deduced, protecting against accidental conversions
    static_assert(sizeof...(ExplicitArgumentBarrier) == 0,
        "Do not give explicit template parameters to Foo()");
}

template <class ExplicitT, int&... ExplicitArgumentBarrier, class U>
void Bar(U const& arg) {
    static_assert(sizeof...(ExplicitArgumentBarrier) == 0,
        "Bar() requires exactly one explicit template parameter");
}

template <class... ExplicitTs, int&... ExplicitArgumentBarrier, class U>
void Baz(U arg) {
    static_assert(sizeof...(ExplicitArgumentBarrier) == 0,
        "Argument type must be deduced in call to Baz()");
}

int main() {
    Foo(42);  // T deduced as int
    Bar<double>("hello");  // U deduced as char[6]
    Baz<int, float, double, char**>(3.14);  // U deduced as double
}
