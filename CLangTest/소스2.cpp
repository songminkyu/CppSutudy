#include <vector> // for demo purposes
#include <typeinfo> // for demo purposes
#include <iostream> // for demo purposes
#include <boost/core/demangle.hpp> // for pretty output
inline auto& get_registered_types() {
    static std::vector<std::string> registered_types = { };
    return registered_types;
}
template <class T> auto register_type() {
    get_registered_types().push_back(
        boost::core::demangle(typeid(T).name()));
    return get_registered_types().size() - 1;
}
template <class Derived> struct RegisteredType {
    inline static std::size_t index = register_type<Derived>();
};
template <class T> struct Foo : RegisteredType<Foo<T>> { };
auto demo() {
    for (auto const& name : get_registered_types()) {
        std::cout << name << " was registered" << std::endl;
    }
    return Foo<int>{}.index + Foo<double>{}.index
        + Foo<char>{}.index + Foo<int>{}.index + Foo<double&>{}.index;
}
int main() { return (demo() != 0) ? 0 : 1; }