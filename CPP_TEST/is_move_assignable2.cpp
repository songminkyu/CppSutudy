#include <iostream>
#include <string>
#include <type_traits>
/*
https://cpprefjp.github.io/reference/type_traits/is_nothrow_invocable.html
*/

/*

****** 프로토 타입 ******

template< class T>
struct is_move_assignable
    : std::is_assignable< typename std::add_lvalue_reference<T>::type,
                          typename std::add_rvalue_reference<T>::type> {};

template< class T>
struct is_trivially_move_assignable
    : std::is_trivially_assignable< typename std::add_lvalue_reference<T>::type,
                                    typename std::add_rvalue_reference<T>::type> {};

template< class T>
struct is_nothrow_move_assignable
    : std::is_nothrow_assignable< typename std::add_lvalue_reference<T>::type,
                                  typename std::add_rvalue_reference<T>::type> {};

*/
struct Foo { int n; };
struct NoMove {
    // prevents implicit declaration of default move assignment operator
    // however, the class is still move-assignable because its
    // copy assignment operator can bind to an rvalue argument
    NoMove& operator=(const NoMove&) { return *this; }
};
int main() {
    std::cout << std::boolalpha
        << "std::string is nothrow move-assignable? "
        << std::is_nothrow_move_assignable<std::string>::value << '\n'
        << "int[2] is move-assignable? "
        << std::is_move_assignable<int[2]>::value << '\n'
        << "Foo is trivally move-assignable? "
        << std::is_trivially_move_assignable<Foo>::value << '\n';

    std::cout << std::boolalpha
        << "NoMove is move-assignable? "
        << std::is_move_assignable<NoMove>::value << '\n'
        << "NoMove is nothrow move-assignable? "
        << std::is_nothrow_move_assignable<NoMove>::value << '\n';
}