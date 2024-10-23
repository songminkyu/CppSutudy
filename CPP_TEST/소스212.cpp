#include <vector> // for demo purposes
#include <typeinfo> // for demo purposes
#include <iostream> // for demo purposes
#include <boost/core/demangle.hpp> // for pretty output

/*
*클래스 템플릿의 모든 전문 화를 위해 무언가(목록 생성과 같은)
* 작업이 필요하십니까? 템플릿 레즈스트라 패턴을 사용하십시오!
*
*  주의사항
*  C++ register_type 의 일관된호출순서를 보장하지 않으므로
* 신중하게 사용하십시오..!!
*/

inline auto& get_registered_types() 
{
    static std::vector<std::string> registered_types = { };
    return registered_types;
}
template <class T> auto register_type() 
{
    get_registered_types().push_back(
        boost::core::demangle(typeid(T).name()));
    return get_registered_types().size() - 1;
}
template <class Derived> struct RegisteredType 
{
    inline static std::size_t index = register_type<Derived>();
};

template <class T> struct Foo : RegisteredType<Foo<T>> { };

auto demo() 
{
    for (auto const& name : get_registered_types()) {
        std::cout << name << " was registered" << std::endl;
    }
    return Foo<int>{}.index + Foo<double>{}.index
        + Foo<char>{}.index + Foo<int>{}.index + Foo<double&>{}.index;
}
int main() { 
    return (demo() != 0) ? 0 : 1;
}