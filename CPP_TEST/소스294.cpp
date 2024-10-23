#include <iostream>
#include <string>
#include <type_traits>
#include <typeinfo>
#include <iomanip>

template<class T>
std::string imp_primary_type_category() {
    std::string ret;

    if constexpr (std::is_void_v<T>)                    ret += "void/";
    if constexpr (std::is_null_pointer_v<T>)            ret += "null_pointer/";
    if constexpr (std::is_integral_v<T>)                ret += "integral/";
    if constexpr (std::is_floating_point_v<T>)          ret += "floating_point/";
    if constexpr (std::is_array_v<T>)                   ret += "array/";
    if constexpr (std::is_pointer_v<T>)                 ret += "pointer/";
    if constexpr (std::is_lvalue_reference_v<T>)        ret += "lvalue_reference/";
    if constexpr (std::is_rvalue_reference_v<T>)        ret += "rvalue_reference/";
    if constexpr (std::is_member_object_pointer_v<T>)   ret += "member_object_pointer/";
    if constexpr (std::is_member_function_pointer_v<T>) ret += "member_function_pointer/";
    if constexpr (std::is_enum_v<T>)                    ret += "enum/";
    if constexpr (std::is_union_v<T>)                   ret += "union/";
    if constexpr (std::is_class_v<T>)                   ret += "class/";
    if constexpr (std::is_function_v<T>)                ret += "function/";
    if (ret.empty())                                    ret += "unknown/";

    return ret;
}

template<class ...TS>
void is_primary_type_category() {
    ((std::cout << std::setw(32) << std::left << typeid(TS).name() << " " << imp_primary_type_category<TS>() << '\n'), ...);
}

struct A {};
enum class EnumA;
union UnionA {};

int main() {
    is_primary_type_category<
        void, std::nullptr_t, char, long double, int[10], void*, int&, int&&, int A::*, void (A::*)(int, int), EnumA, UnionA, A, int(int, int)>();
    return 0;
}
